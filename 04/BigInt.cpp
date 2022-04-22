#include "BigInt.hpp"

#include <cstdlib>

BigInt::BigInt(const std::string& str)
{
	m_size = str.size();
	m_num = new uint16_t[m_size];

	for (size_t i = m_size; i > 0; --i)
		m_num[m_size - i] = str[i - 1] - '0';
}

BigInt::BigInt(uint32_t number)
    : BigInt(std::to_string(number))
{
}

BigInt::BigInt(const BigInt& other)
{
	m_num = new uint16_t[other.m_size];
	m_size = other.m_size;
	for (size_t i = 0; i < m_size; i++)
		m_num[i] = other.m_num[i];
};

BigInt BigInt::operator-(const BigInt& other) const
{
	size_t minLen = std::min(m_size, other.m_size);
	size_t maxLen = std::max(m_size, other.m_size);

	BigInt result = BigInt(std::string(maxLen, '0'));

	for (size_t i = 0; i < minLen; ++i) {
		if (m_num[i] < other.m_num[i]) {
			m_num[i] += 10;
			m_num[i + 1] -= 1;
		}

		result.m_num[i] = m_num[i] - other.m_num[i];
	}

	return result;
}

BigInt BigInt::operator-(uint32_t other) const
{
	BigInt num = BigInt(other);
	return this->operator-(num);
}

BigInt BigInt::operator+(const BigInt& other) const
{
	size_t minLen = std::min(m_size, other.m_size);
	size_t maxLen = std::max(m_size, other.m_size);

	BigInt result = BigInt(std::string(maxLen + 1, '0'));
	uint16_t residual = 0;

	for (size_t i = 0; i < minLen; ++i) {
		result.m_num[i] = (m_num[i] + other.m_num[i] + residual) % 10;
		residual = (m_num[i] + other.m_num[i]) / 10;
	}

	for (size_t i = minLen; i < maxLen; ++i) {
		uint16_t tmp = m_size > other.m_size ? m_num[i] : other.m_num[i];
		result.m_num[i] = (tmp + residual) % 10;
		residual = (tmp + residual) / 10;
	}

	result.m_num[maxLen] = residual;

	return result;
}

BigInt BigInt::operator+(uint32_t other) const
{
	BigInt num = BigInt(other);
	return this->operator+(num);
}

BigInt BigInt::operator*(const BigInt& other) const
{
	if (m_size < other.m_size)
		return productOf(other, *this);
	return productOf(*this, other);
}

BigInt BigInt::productOf(const BigInt& longer, const BigInt& shorter) const
{
	size_t minLen = shorter.m_size;
	size_t maxLen = longer.m_size;

	BigInt result = BigInt(std::string(maxLen * maxLen + 1, '0'));
	for (size_t i = 0; i < minLen; ++i) {
		BigInt buffer = BigInt(std::string(maxLen * maxLen + 1, '0'));
		uint16_t residual = 0;
		for (size_t j = 0; j < maxLen; ++j) {
			buffer.m_num[j + i] = (shorter.m_num[i] * longer.m_num[j] + residual) % 10;
			residual = (shorter.m_num[i] * longer.m_num[j]) / 10;
		}
		buffer.m_num[maxLen + i] = residual;
		result = result + buffer;
	}

	return result;
}

BigInt& BigInt::operator=(const BigInt& other)
{
	if (m_size != other.m_size) {
		delete[] m_num;
		m_num = new uint16_t[other.m_size];
		m_size = other.m_size;
	}

	for (size_t i = 0; i < m_size; ++i)
		m_num[i] = other.m_num[i];

	return *this;
};

BigInt& BigInt::operator=(BigInt&& other)
{
	if (*this == other)
		return *this;

	delete[] m_num;
	m_num = other.m_num;
	m_size = other.m_size;
	other.m_num = nullptr;
	other.m_size = 0;
	return *this;
};

bool BigInt::operator<(const BigInt& other) const
{

	size_t i = m_size;
	while (m_num[i-- - 1] == 0) { }

	size_t j = other.m_size;
	while (other.m_num[j-- - 1] == 0) { }

	if (m_size - i > other.m_size - j)
		return false;
	if (m_size - i < other.m_size - j)
		return true;

	for (size_t i = m_size; i > 0; --i)
		if (m_num[i - 1] > other.m_num[i - 1])
			return false;
	return true;
}

bool BigInt::operator==(const BigInt& other) const
{
	if (m_size != other.m_size)
		return false;

	for (size_t i = m_size; i > 0; --i)
		if (m_num[i - 1] != other.m_num[i - 1])
			return false;
	return true;
}

bool BigInt::operator!=(const BigInt& other) const
{
	return !(*this == other);
}

bool BigInt::operator<=(const BigInt& other) const
{
	return (*this < other) || (*this == other);
}

bool BigInt::operator>(const BigInt& other) const
{
	return !(*this <= other);
}

bool BigInt::operator>=(const BigInt& other) const
{
	return !(*this < other);
}

BigInt::~BigInt()
{
	delete[] m_num;
}

std::ostream& operator<<(std::ostream& os, const BigInt& num)
{
	size_t i = num.m_size;
	while (num.m_num[i-- - 1] == 0) { }
	for (i++; i > 0; --i)
		os << num.m_num[i - 1];

	return os;
}