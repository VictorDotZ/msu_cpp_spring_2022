#include <sstream>

#include "Deserializer.hpp"
#include "Serializer.hpp"

#include <gtest/gtest.h>

struct SingleBoolData {
	bool a;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a);
	}
};

struct SingleUintData {
	uint64_t a;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a);
	}
};

struct MixedData {
	uint64_t a;
	bool b;
	bool c;
	uint64_t d;
	uint64_t e;
	bool f;
	uint64_t g;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c, d, e, f, g);
	}
};

class TestSerialization : public ::testing::Test {
};

TEST_F(TestSerialization, SingleBoolField)
{
	SingleBoolData x { true };
	std::stringstream s1;

	Serializer serializer(s1);
	ASSERT_EQ(serializer.save(x), Error::NoError);

	SingleBoolData y { false };
	Deserializer d1(s1);

	ASSERT_EQ(d1.load(y), Error::NoError);

	ASSERT_EQ(x.a, y.a);

	auto s2 = std::stringstream("");
	Deserializer d2(s2);
	ASSERT_EQ(d2.load(y), Error::CorruptedArchive);

	auto s3 = std::stringstream("1");
	Deserializer d3(s3);
	ASSERT_EQ(d3.load(y), Error::CorruptedArchive);

	y = { true };

	auto s4 = std::stringstream("false");
	Deserializer d4(s4);
	ASSERT_EQ(d4.load(y), Error::NoError);

	ASSERT_EQ(y.a, false);

	y = { true };

	auto s5 = std::stringstream("0");
	Deserializer d5(s5);
	ASSERT_EQ(d5.load(y), Error::CorruptedArchive);

	auto s6 = std::stringstream("1");
	Deserializer d6(s6);
	ASSERT_EQ(d6.load(y), Error::CorruptedArchive);

	auto s7 = std::stringstream("1false");
	Deserializer d7(s7);
	ASSERT_EQ(d7.load(y), Error::CorruptedArchive);

	auto s8 = std::stringstream("false0");
	Deserializer d8(s8);
	ASSERT_EQ(d8.load(y), Error::CorruptedArchive);

	auto s9 = std::stringstream("18446744073709551616");
	Deserializer d9(s9);
	ASSERT_EQ(d9.load(y), Error::CorruptedArchive);
}

TEST_F(TestSerialization, SingleUintField)
{
	SingleUintData x { 100 };
	std::stringstream s1;

	Serializer serializer(s1);
	ASSERT_EQ(serializer.save(x), Error::NoError);

	SingleUintData y { false };
	Deserializer d1(s1);

	ASSERT_EQ(d1.load(y), Error::NoError);

	ASSERT_EQ(x.a, y.a);

	auto s2 = std::stringstream("");
	Deserializer d2(s2);
	ASSERT_EQ(d2.load(y), Error::CorruptedArchive);

	auto s3 = std::stringstream("true");
	Deserializer d3(s3);
	ASSERT_EQ(d3.load(y), Error::CorruptedArchive);

	auto s4 = std::stringstream("-100");
	Deserializer d4(s4);
	ASSERT_EQ(d4.load(y), Error::CorruptedArchive);

	y = { 100 };

	auto s5 = std::stringstream("200");
	Deserializer d5(s5);
	ASSERT_EQ(d5.load(y), Error::NoError);

	ASSERT_EQ(y.a, 200);

	y = { 100 };

	auto s6 = std::stringstream("0");
	Deserializer d6(s6);
	ASSERT_EQ(d6.load(y), Error::NoError);

	ASSERT_EQ(y.a, 0);

	auto s7 = std::stringstream("1");
	Deserializer d7(s7);
	ASSERT_EQ(d7.load(y), Error::NoError);

	ASSERT_EQ(y.a, 1);

	auto s8 = std::stringstream("18446744073709551615");
	Deserializer d8(s8);
	ASSERT_EQ(d8.load(y), Error::NoError);

	ASSERT_EQ(y.a, UINT64_MAX);

	auto s9 = std::stringstream("18446744073709551616");
	Deserializer d9(s9);
	ASSERT_EQ(d9.load(y), Error::CorruptedArchive);

	auto s10 = std::stringstream("42str");
	Deserializer d10(s10);
	ASSERT_EQ(d10.load(y), Error::CorruptedArchive);

	auto s11 = std::stringstream("0false");
	Deserializer d11(s11);
	ASSERT_EQ(d11.load(y), Error::CorruptedArchive);
}

TEST_F(TestSerialization, MixedFields)
{
	MixedData x { 100, true, false, 200, 300, false, 400 };
	std::stringstream s1;

	Serializer serializer(s1);
	ASSERT_EQ(serializer.save(x), Error::NoError);

	MixedData y { 0, false, false, 0, 0, false, 0 };
	Deserializer d1(s1);

	ASSERT_EQ(d1.load(y), Error::NoError);

	ASSERT_EQ(x.a, y.a);
	ASSERT_EQ(x.b, y.b);
	ASSERT_EQ(x.c, y.c);
	ASSERT_EQ(x.d, y.d);
	ASSERT_EQ(x.e, y.e);
	ASSERT_EQ(x.f, y.f);
	ASSERT_EQ(x.g, y.g);

	auto s2 = std::stringstream("");
	Deserializer d2(s2);
	ASSERT_EQ(d2.load(y), Error::CorruptedArchive);

	auto s3 = std::stringstream("100 1 false 200 300 false 400");
	Deserializer d3(s3);
	ASSERT_EQ(d3.load(y), Error::CorruptedArchive);

	auto s4 = std::stringstream("100 true false -200 300 false 400");
	Deserializer d4(s4);
	ASSERT_EQ(d4.load(y), Error::CorruptedArchive);

	auto s5 = std::stringstream("100 true false 200 300 false"); // deficiency
	Deserializer d5(s5);
	ASSERT_EQ(d5.load(y), Error::CorruptedArchive);

	y = { 0, true, true, 0, 0, true, 0 };

	auto s6 = std::stringstream("100 false true 200 300 false 600");
	Deserializer d6(s6);
	ASSERT_EQ(d6.load(y), Error::NoError);

	ASSERT_EQ(y.a, 100);
	ASSERT_EQ(y.b, false);
	ASSERT_EQ(y.c, true);
	ASSERT_EQ(y.d, 200);
	ASSERT_EQ(y.e, 300);
	ASSERT_EQ(y.f, false);
	ASSERT_EQ(y.g, 600);

	y = { 0, true, true, 0, 0, true, 0 };

	auto s7 = std::stringstream("100 false true 200 300 false 600 777"); // overabundance
	Deserializer d7(s7);
	ASSERT_EQ(d7.load(y), Error::CorruptedArchive);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
