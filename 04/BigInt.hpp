#pragma once
#include <cstdint>
#include <ostream>
#include <string>

class BigInt {
public:
	BigInt(const std::string& s);
	BigInt(uint32_t number);
	BigInt(const BigInt& other);

	BigInt operator-(const BigInt& other) const;
	BigInt operator-(uint32_t other) const;

	BigInt operator+(const BigInt& other) const;
	BigInt operator+(uint32_t other) const;

	BigInt operator*(const BigInt& other) const;

	BigInt& operator=(const BigInt& other);
	BigInt& operator=(BigInt&& other);

	bool operator<(const BigInt& other) const;
	bool operator<=(const BigInt& other) const;
	bool operator==(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator>(const BigInt& other) const;
	bool operator>=(const BigInt& other) const;

	~BigInt();

	friend std::ostream& operator<<(std::ostream& os, const BigInt& num);

private:
	BigInt productOf(const BigInt& longer, const BigInt& shorter) const;

	uint16_t m_base = 10;
	uint16_t* m_num = nullptr;
	size_t m_size = 0;
};