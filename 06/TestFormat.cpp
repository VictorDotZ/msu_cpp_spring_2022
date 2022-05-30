#define EXPECT_THROW_WITH_MESSAGE(stmt, etype, whatstring) EXPECT_THROW( \
	try {                                                                \
		stmt;                                                            \
	} catch (const etype& ex) {                                          \
		EXPECT_EQ(std::string(ex.what()), whatstring);                   \
		throw;                                                           \
	},                                                                   \
	etype)

#include "Format.hpp"

#include <gtest/gtest.h>

class TestFormat : public ::testing::Test {
};

TEST_F(TestFormat, defaultUseCase)
{
	ASSERT_EQ(format(""), "");
	ASSERT_EQ(format("Hello World!"), "Hello World!");
	ASSERT_EQ(format("{0}", "test"), "test");
	ASSERT_EQ(format("Hello {0} World!", "my"), "Hello my World!");
	ASSERT_EQ(format("{0}{0}{0} {0}{0}", "ora"), "oraoraora oraora");
	ASSERT_EQ(format("{0} + {1} = {2}", 5, 6, 11), "5 + 6 = 11");
	ASSERT_EQ(format("{0} {3} {1} = {2}", 5, 6, 11, '+'), "5 + 6 = 11");
	ASSERT_EQ(format("{1} + {1} = {0}", 20, "ten"), "ten + ten = 20");
	ASSERT_EQ(format("{1}{2} = {0}", 100, 10, 0), "100 = 100");
	ASSERT_EQ(format("{1} / {2} = {0}", "2.0", 7, 3.5), "7 / 3.5 = 2.0");
}

TEST_F(TestFormat, extraBraces)
{
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{{1} = {0}", 2, "one"),
	    TemplateStringWrongFormat,
	    "Incorrect positional number");
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{1}} = {0}", 2, "one"),
	    TemplateStringWrongFormat,
	    "} before {");
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{1} = {0", 2, "one"),
	    TemplateStringWrongFormat,
	    "No paired }");
}

TEST_F(TestFormat, manyArgs)
{
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{1} = {0}", 2, 1, 33),
	    ArgumentMissing,
	    "Args too many");
}

TEST_F(TestFormat, littleArgs)
{
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{1} = {0}", 2),
	    ArgumentMissing,
	    "Args too little");
}

TEST_F(TestFormat, incorrectPositionalNumber)
{
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{1one} = {0}", 2, 1),
	    TemplateStringWrongFormat,
	    "Incorrect positional number");
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{one} = {0}", 2, 1),
	    TemplateStringWrongFormat,
	    "Incorrect positional number");
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{} = {0}", 2, 1),
	    TemplateStringWrongFormat,
	    "Incorrect positional number");
	EXPECT_THROW_WITH_MESSAGE(
	    format("{1}+{18446744073709551616} = {0}", 2, 1),
	    TemplateStringWrongFormat,
	    "Incorrect positional number");
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
