#pragma once

#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

class FileSort {
public:
	FileSort(std::string inputPath, std::string outputPath,
	    const size_t chunkSize);

	void startSorting();

	~FileSort();

private:
	void readChunkFromFileToVec(std::vector<uint64_t>& chunkData,
	    std::ifstream& input);

	void writeChunkFromVecToFile(std::vector<uint64_t>& chunkData,
	    const std::string& outputPathLocal);

	void createSortedChunks();

	void mergeSortedChunks();

	void mergeChunks(const std::string& candidate1Name,
	    const std::string& candidate2Name,
	    const std::string& outputPathLocal);

	const std::string m_tmpPath = "/var";
	const std::string m_inputPath;
	const std::string m_outputPath;
	const size_t m_chunkSize;
	std::stack<std::string> m_sortedChunkFilenames;
};