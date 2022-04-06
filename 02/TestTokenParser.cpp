#include "TokenParser.hpp"

#include <gtest/gtest.h>
#include <vector>

class TestTokenParser : public ::testing::Test {
protected:
	void SetUp()
	{
		parser = new TokenParser();

		parser->setStartCallback(startCallback);
		parser->setEndCallback(endCallback);
		parser->setStringTokenCallback(stringTokenCallback);
		parser->setDigitTokenCallback(digitTokenCallback);

		stringTokens = new std::vector<std::string>();
		digitTokens = new std::vector<uint64_t>();
	}

	void TearDown()
	{
		delete parser;

		delete stringTokens;
		delete digitTokens;
	}

	TokenParser* parser;

	std::function<void(std::string&)> stringTokenCallback = [&](std::string& str) {
		stringTokensCount++;
		tokensCount++;
		stringTokens->push_back(str.substr());
	};

	std::function<void(uint64_t)> digitTokenCallback = [&](uint64_t digit) {
		digitTokensCount++;
		tokensCount++;
		digitTokens->push_back(digit);
	};

	std::function<void()> startCallback = []() {};
	std::function<void()> endCallback = []() {};

	size_t tokensCount = 0;
	size_t stringTokensCount = 0;
	size_t digitTokensCount = 0;
	std::vector<std::string>* stringTokens;
	std::vector<uint64_t>* digitTokens;
};

TEST_F(TestTokenParser, emptyString)
{
	std::string str = "";

	parser->parse(str);

	ASSERT_EQ(tokensCount, 0);
	ASSERT_EQ(stringTokensCount, 0);
	ASSERT_EQ(digitTokensCount, 0);
}

TEST_F(TestTokenParser, separatorsOnlyString)
{
	std::string str = "\n  \t\n \n\t  \t\t \n\n  \t ";

	parser->parse(str);

	ASSERT_EQ(tokensCount, 0);
	ASSERT_EQ(stringTokensCount, 0);
	ASSERT_EQ(digitTokensCount, 0);
}

TEST_F(TestTokenParser, onlyOneDigitToken)
{
	std::string str = "0";

	parser->parse(str);

	ASSERT_EQ(tokensCount, 1);
	ASSERT_EQ(stringTokensCount, 0);
	ASSERT_EQ(digitTokensCount, 1);

	ASSERT_EQ(*digitTokens->begin(), 0);
}

TEST_F(TestTokenParser, onlyDigitTokens)
{
	std::string str = "\t\t\n050\t\n83562893\t\n 0 \t 01234567890 \n\t 9876543210";

	parser->parse(str);

	ASSERT_EQ(tokensCount, 5);
	ASSERT_EQ(stringTokensCount, 0);
	ASSERT_EQ(digitTokensCount, 5);

	std::vector<uint64_t> trueDigitTokens = { 50, 83562893, 0, 1234567890, 9876543210 };

	ASSERT_EQ(digitTokens->size(), trueDigitTokens.size());

	for (size_t i = 0; i < digitTokens->size(); ++i)
		EXPECT_EQ(digitTokens->at(i), trueDigitTokens[i]);
}

TEST_F(TestTokenParser, onlyOneStringToken)
{
	std::string str = "y";

	parser->parse(str);

	ASSERT_EQ(tokensCount, 1);
	ASSERT_EQ(stringTokensCount, 1);
	ASSERT_EQ(digitTokensCount, 0);

	ASSERT_EQ(*stringTokens->begin(), "y");
}

TEST_F(TestTokenParser, onlyStringTokens)
{
	std::string str = "\t\t\nhello\t\nworld\t\n rhf784fufhwj \t h\n\t ";

	parser->parse(str);

	ASSERT_EQ(tokensCount, 4);
	ASSERT_EQ(stringTokensCount, 4);
	ASSERT_EQ(digitTokensCount, 0);

	std::vector<std::string> trueStringTokens = { "hello", "world", "rhf784fufhwj", "h" };

	ASSERT_EQ(stringTokens->size(), trueStringTokens.size());

	for (size_t i = 0; i < stringTokens->size(); ++i)
		EXPECT_EQ(stringTokens->at(i), trueStringTokens[i]);
}

TEST_F(TestTokenParser, digitAndStringTokens)
{
	std::string str = "hello\n\t050\tworld \n\t 83562893\n0   h rhf784fufhwj\t\n01234567890 9876543210";

	parser->parse(str);

	ASSERT_EQ(tokensCount, 9);
	ASSERT_EQ(stringTokensCount, 4);
	ASSERT_EQ(digitTokensCount, 5);

	std::vector<std::string> trueStringTokens = { "hello", "world", "h", "rhf784fufhwj" };
	std::vector<uint64_t> trueDigitTokens = { 50, 83562893, 0, 1234567890, 9876543210 };

	ASSERT_EQ(stringTokens->size(), trueStringTokens.size());

	for (size_t i = 0; i < stringTokens->size(); ++i)
		EXPECT_EQ(stringTokens->at(i), trueStringTokens[i]);

	ASSERT_EQ(digitTokens->size(), trueDigitTokens.size());

	for (size_t i = 0; i < digitTokens->size(); ++i)
		EXPECT_EQ(digitTokens->at(i), trueDigitTokens[i]);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}