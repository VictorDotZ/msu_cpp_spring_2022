#pragma once

#include <cstring>
#include <thread>
#include <vector>

template <class T>
void merge(std::vector<T>& array, size_t left, size_t mid, size_t right)
{
	size_t it1 = 0;
	size_t it2 = 0;
	std::vector<T> result(right - left);

	while ((left + it1 < mid) && (mid + it2 < right)) {
		if (array[left + it1] < array[mid + it2]) {
			result[it1 + it2] = array[left + it1];
			it1++;
		} else {
			result[it1 + it2] = array[mid + it2];
			it2++;
		}
	}

	std::memcpy(&result[it1 + it2], &array[left + it1], (mid - left - it1) * sizeof(T));
	std::memcpy(&result[mid - left + it2], &array[mid + it2], (right - mid - it2) * sizeof(T));
	std::memcpy(&array[left], &result[0], result.size() * sizeof(T));
}

template <class T>
void mergeSort(std::vector<T>& array)
{
	for (size_t i = 1; i < array.size(); i *= 2)
		for (size_t j = 0; j < array.size() - i; j += 2 * i)
			merge(array, j, j + i, std::min(j + 2 * i, array.size()));
}

template <class T>
void mergeSortMT(std::vector<T>& array)
{
	size_t mid = array.size() / 2;
	std::vector<T> leftHalf(mid);
	std::vector<T> rightHalf(array.size() - mid);

	std::memcpy(&leftHalf[0], &array[0], leftHalf.size() * sizeof(T));
	std::memcpy(&rightHalf[0], &array[mid], rightHalf.size() * sizeof(T));

	std::thread sortLeft(mergeSort<T>, std::ref(leftHalf));
	std::thread sortRight(mergeSort<T>, std::ref(rightHalf));

	sortLeft.join();
	sortRight.join();

	array = leftHalf;
	std::move(rightHalf.begin(), rightHalf.end(), std::back_inserter(array));
	merge(array, 0, mid, array.size());
}