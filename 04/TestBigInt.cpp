#include "BigInt.hpp"

#include <gtest/gtest.h>

#include <climits>
#include <iostream>

class TestBitInt : public ::testing::Test {
};

TEST_F(TestBitInt, addition)
{
	BigInt num1 = BigInt("555");
	BigInt num2 = BigInt("77");

	std::stringstream result;
	result << (num1 + num2);

	ASSERT_EQ(result.str(), "632");

	result.str(std::string());
	result.clear();
	result << (num2 + num1);

	ASSERT_EQ(result.str(), "632");

	num1 = BigInt("555");
	num2 = BigInt("0");

	result.str(std::string());
	result.clear();
	result << (num1 + num2);

	ASSERT_EQ(result.str(), "555");

	result.str(std::string());
	result.clear();
	result << (num2 + num1);

	ASSERT_EQ(result.str(), "555");

	num1 = BigInt(std::to_string(ULLONG_MAX));
	num2 = BigInt(std::to_string(ULLONG_MAX));

	result.str(std::string());
	result.clear();
	result << (num2 + num1);

	ASSERT_EQ(result.str(), "36893488147419103230");
}

TEST_F(TestBitInt, subtraction)
{
	BigInt num1 = BigInt("555");
	BigInt num2 = BigInt("77");

	std::stringstream result;
	result << (num1 - num2);

	ASSERT_EQ(result.str(), "478");

	num1 = BigInt("555");
	num2 = BigInt("0");

	result.str(std::string());
	result.clear();
	result << (num1 - num2);

	ASSERT_EQ(result.str(), "555");

	num1 = BigInt("36893488147419103230");
	num2 = BigInt(std::to_string(ULLONG_MAX));

	result.str(std::string());
	result.clear();
	result << (num1 - num2);

	ASSERT_EQ(result.str(), std::to_string(ULLONG_MAX));
}

TEST_F(TestBitInt, multiplication)
{
	BigInt num1 = BigInt("555");
	BigInt num2 = 77;

	std::stringstream result;
	result << (num1 * num2);

	ASSERT_EQ(result.str(), "42735");

	num1 = BigInt("555");
	num2 = BigInt("77");

	result.str(std::string());
	result.clear();
	result << (num1 * num2);

	ASSERT_EQ(result.str(), "42735");

	result.str(std::string());
	result.clear();
	result << (num2 * num1);

	ASSERT_EQ(result.str(), "42735");

	num1 = BigInt("555");
	num2 = BigInt("0");

	result.str(std::string());
	result.clear();
	result << (num1 * num2);

	ASSERT_EQ(result.str(), "0");

	result.str(std::string());
	result.clear();
	result << (num2 * num1);

	ASSERT_EQ(result.str(), "0");

	num1 = BigInt(std::to_string(ULLONG_MAX));
	num2 = BigInt("99");

	result.str(std::string());
	result.clear();
	result << (num1 * num2);

	ASSERT_EQ(result.str(), "1826227663297245609885");

	num1 = BigInt(std::to_string(ULLONG_MAX));
	num2 = BigInt(std::to_string(ULLONG_MAX));

	result.str(std::string());
	result.clear();
	result << (num1 * num2);

	ASSERT_EQ(result.str(), "340282366920938463426481119284349108225");

	num1 = BigInt("12304567");
	num2 = BigInt("12304567");

	result.str(std::string());
	result.clear();
	result << (num1 * num2);

	ASSERT_EQ(result.str(), "151402369057489");
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}