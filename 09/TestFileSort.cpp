#include "FileSort.hpp"
#include "MergeSort.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

#include <gtest/gtest.h>

class TestFileSort : public ::testing::Test {
protected:
	void SetUp()
	{
		std::random_device rnd_device;
		std::mt19937 mersenne_engine { rnd_device() };
		std::uniform_int_distribution<uint64_t> dist { 0, UINT64_MAX };

		auto gen = [&dist, &mersenne_engine]() {
			return dist(mersenne_engine);
		};

		randomVector = new std::vector<uint64_t>(5 * 1e6); // 40 MB
		generate(begin(*randomVector), end(*randomVector), gen);

		std::ofstream randomFile("./data.dat", std::ios::binary);

		if (!randomFile.is_open()) {
			randomFile.close();
			throw std::runtime_error("file open error");
		}
		randomFile.write(reinterpret_cast<const char*>(randomVector->data()),
		    static_cast<std::streamsize>(randomVector->size() * sizeof(uint64_t)));

		if (!randomFile.good()) {
			randomFile.close();
			throw std::runtime_error("Write to disk error");
		}
		randomFile.close();

		sortedVector = new std::vector<uint64_t>(*randomVector);

		sort(sortedVector->begin(), sortedVector->end());
	}

	void TearDown()
	{
		delete randomVector;
		delete sortedVector;
	}

	std::vector<uint64_t>* randomVector;
	std::vector<uint64_t>* sortedVector;
};

TEST_F(TestFileSort, defaultUseCase)
{
	FileSort fileSort("data.dat", "result.dat", 100000); // less than 1 MB
	fileSort.startSorting();

	std::vector<uint64_t> vector(randomVector->size());

	std::ifstream input("result.dat", std::ios::binary);
	if (!input.is_open()) {
		input.close();
		throw std::runtime_error("file open error");
	}

	input.read(reinterpret_cast<char*>(vector.data()),
	    static_cast<std::streamsize>(vector.size() * sizeof(uint64_t)));

	ASSERT_EQ(vector, *sortedVector);

	if (!input.good()) {
		input.close();
		throw std::runtime_error("Invalid input");
	}
	input.close();
}

TEST_F(TestFileSort, mergeSort)
{
	mergeSort<uint64_t>(*randomVector);
	ASSERT_EQ(*randomVector, *sortedVector);
}

TEST_F(TestFileSort, mergeSortMT)
{
	mergeSortMT<uint64_t>(*randomVector);
	ASSERT_EQ(*randomVector, *sortedVector);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}