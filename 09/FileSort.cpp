#include "FileSort.hpp"
#include "MergeSort.hpp"

FileSort::FileSort(std::string inputPath, std::string outputPath,
    const size_t chunkSize)
    : m_inputPath(std::move(inputPath))
    , m_outputPath(std::move(outputPath))
    , m_chunkSize(chunkSize)
{
}

void FileSort::startSorting()
{
	try {
		createSortedChunks();
		mergeSortedChunks();
	} catch (std::runtime_error& ex) {
		std::cerr << ex.what() << '\n';
	}
}

FileSort::~FileSort()
{
	while (!m_sortedChunkFilenames.empty()) {
		std::string fileName = m_sortedChunkFilenames.top();
		m_sortedChunkFilenames.pop();
		std::remove((m_tmpPath + fileName).c_str());
	}
}

void FileSort::readChunkFromFileToVec(std::vector<uint64_t>& chunkData, std::ifstream& input)
{
	input.read(reinterpret_cast<char*>(chunkData.data()),
	    static_cast<std::streamsize>(chunkData.size() * sizeof(uint64_t)));
}

void FileSort::writeChunkFromVecToFile(std::vector<uint64_t>& chunkData,
    const std::string& outputPathLocal)
{
	std::ofstream output(outputPathLocal, std::ios::binary);
	if (!output.is_open()) {
		output.close();
		throw std::runtime_error("file open error");
	}
	output.write(reinterpret_cast<const char*>(chunkData.data()),
	    static_cast<std::streamsize>(chunkData.size() * sizeof(uint64_t)));
	if (!output.good()) {
		output.close();
		throw std::runtime_error("Write to disk error");
	}
	output.close();
}

void FileSort::createSortedChunks()
{
	std::vector<uint64_t> chunkData(m_chunkSize);
	std::ifstream input(m_inputPath, std::ios::binary | std::ios::ate);
	if (!input.is_open()) {
		input.close();
		throw std::runtime_error("file open error");
	}

	size_t fileLength = static_cast<size_t>(input.tellg()) / sizeof(uint64_t);
	input.seekg(0);
	while (input.good() && m_chunkSize == chunkData.size()) {
		if (fileLength - static_cast<size_t>(input.tellg()) / sizeof(uint64_t) < m_chunkSize)
			chunkData.resize(fileLength - static_cast<size_t>(input.tellg()) / sizeof(uint64_t));
		readChunkFromFileToVec(chunkData, input);
		mergeSortMT<uint64_t>(chunkData);
		std::string tmpName = std::tmpnam(nullptr);
		m_sortedChunkFilenames.push(std::move(tmpName));
		writeChunkFromVecToFile(chunkData, m_tmpPath + m_sortedChunkFilenames.top());
	}
	if (!input.good()) {
		input.close();
		throw std::runtime_error("Invalid input");
	}
	input.close();
}

void FileSort::mergeSortedChunks()
{
	if (m_sortedChunkFilenames.size() == 1) {
		std::string candidateName = m_sortedChunkFilenames.top();

		std::ifstream candidate(m_tmpPath + candidateName, std::ios::binary);
		std::ofstream output(m_outputPath, std::ios::binary);

		if (!candidate.is_open() || !output.is_open()) {
			candidate.close();
			output.close();
			throw std::runtime_error("process error");
		}

		uint64_t tmp;
		while (!candidate.eof()) {
			candidate.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
			output.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
		}

		if (!candidate.eof()) {
			candidate.close();
			output.close();
			throw std::runtime_error("process error");
		}

		candidate.close();
		output.close();
		m_sortedChunkFilenames.pop();
		std::remove((m_tmpPath + candidateName).c_str());
		return;
	}

	while (m_sortedChunkFilenames.size() > 2) {
		std::string candidate1Name = m_sortedChunkFilenames.top();
		m_sortedChunkFilenames.pop();
		std::string candidate2Name = m_sortedChunkFilenames.top();
		m_sortedChunkFilenames.push(candidate1Name);

		std::string tmpName = std::tmpnam(nullptr);
		m_sortedChunkFilenames.push(std::move(tmpName));

		mergeChunks(m_tmpPath + candidate1Name,
		    m_tmpPath + candidate2Name,
		    m_tmpPath + m_sortedChunkFilenames.top());

		std::string saveTop = m_sortedChunkFilenames.top();
		m_sortedChunkFilenames.pop();
		std::remove((m_tmpPath + candidate1Name).c_str());
		m_sortedChunkFilenames.pop();
		std::remove((m_tmpPath + candidate2Name).c_str());
		m_sortedChunkFilenames.pop();
		m_sortedChunkFilenames.push(std::move(saveTop));
	}

	std::string candidate1Name = m_sortedChunkFilenames.top();
	m_sortedChunkFilenames.pop();
	std::string candidate2Name = m_sortedChunkFilenames.top();
	m_sortedChunkFilenames.push(candidate1Name);

	mergeChunks(m_tmpPath + candidate1Name,
	    m_tmpPath + candidate2Name,
	    m_outputPath);

	std::remove((m_tmpPath + candidate1Name).c_str());
	m_sortedChunkFilenames.pop();
	std::remove((m_tmpPath + candidate2Name).c_str());
	m_sortedChunkFilenames.pop();
}

void FileSort::mergeChunks(const std::string& candidate1Name,
    const std::string& candidate2Name,
    const std::string& outputPathLocal)
{
	uint64_t value1;
	uint64_t value2;
	std::ifstream candidate1(candidate1Name, std::ios::binary);
	std::ifstream candidate2(candidate2Name, std::ios::binary);
	std::ofstream output(outputPathLocal, std::ios::binary);

	if (!output.is_open() || !candidate1.is_open() || !candidate2.is_open()) {
		candidate1.close();
		candidate2.close();
		output.close();
		throw std::runtime_error("File reading error");
	}
	candidate1.read(reinterpret_cast<char*>(&value1), sizeof(value1));
	candidate2.read(reinterpret_cast<char*>(&value2), sizeof(value2));

	while (!candidate1.eof() && !candidate2.eof()) {
		if (value1 < value2) {
			output.write(reinterpret_cast<char*>(&value1), sizeof(value1));
			candidate1.read(reinterpret_cast<char*>(&value1), sizeof(value1));
		} else {
			output.write(reinterpret_cast<char*>(&value2), sizeof(value2));
			candidate2.read(reinterpret_cast<char*>(&value2), sizeof(value2));
		}
	}
	while (!candidate1.eof()) {
		output.write(reinterpret_cast<char*>(&value1), sizeof(value1));
		candidate1.read(reinterpret_cast<char*>(&value1), sizeof(value1));
	}
	while (!candidate2.eof()) {
		output.write(reinterpret_cast<char*>(&value2), sizeof(value2));
		candidate2.read(reinterpret_cast<char*>(&value2), sizeof(value2));
	}
	if (!output.good() || !candidate1.eof() || !candidate2.eof()) {
		candidate1.close();
		candidate2.close();
		output.close();
		throw std::runtime_error("File merge error");
	}

	candidate1.close();
	candidate2.close();
	output.close();
}