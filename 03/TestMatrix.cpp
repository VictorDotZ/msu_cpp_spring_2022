#include "Matrix.hpp"

#include <gtest/gtest.h>

class TestMatrix : public ::testing::Test {
};

TEST_F(TestMatrix, zeroShape)
{
	EXPECT_THROW({
		try {
			Matrix matrix = Matrix(0, 0);
		} catch (const std::invalid_argument& e) {
			throw;
		}
	},
	    std::invalid_argument);

	EXPECT_THROW({
		try {
			Matrix matrix = Matrix(0, 1);
		} catch (const std::invalid_argument& e) {
			throw;
		}
	},
	    std::invalid_argument);

	EXPECT_THROW({
		try {
			Matrix matrix = Matrix(1, 0);
		} catch (const std::invalid_argument& e) {
			throw;
		}
	},
	    std::invalid_argument);
}

TEST_F(TestMatrix, bounds)
{
	Matrix matrix = Matrix(2, 3);

	ASSERT_EQ(matrix.rows(), 2);
	ASSERT_EQ(matrix.columns(), 3);

	EXPECT_THROW({
		try {
			matrix[0][4];
		} catch (const std::out_of_range& e) {
			throw;
		}
	},
	    std::out_of_range);

	EXPECT_THROW({
		try {
			matrix[5][0];
		} catch (const std::out_of_range& e) {
			throw;
		}
	},
	    std::out_of_range);
}

TEST_F(TestMatrix, initializationAndMultiplication)
{
	Matrix matrix = Matrix(2, 3);

	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix[i][j] = 1 + i + j;

	ASSERT_EQ(matrix[0][0], 1);
	ASSERT_EQ(matrix[0][1], 2);
	ASSERT_EQ(matrix[0][2], 3);
	ASSERT_EQ(matrix[1][0], 2);
	ASSERT_EQ(matrix[1][1], 3);
	ASSERT_EQ(matrix[1][2], 4);

	matrix *= 10;

	ASSERT_EQ(matrix[0][0], 10);
	ASSERT_EQ(matrix[0][1], 20);
	ASSERT_EQ(matrix[0][2], 30);
	ASSERT_EQ(matrix[1][0], 20);
	ASSERT_EQ(matrix[1][1], 30);
	ASSERT_EQ(matrix[1][2], 40);
}

TEST_F(TestMatrix, equality)
{
	Matrix matrix1 = Matrix(2, 3);

	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix1[i][j] = 1 + i + j;

	ASSERT_TRUE(matrix1 == matrix1);
	ASSERT_FALSE(matrix1 != matrix1);

	Matrix matrix2 = Matrix(2, 3);

	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix2[i][j] = 1 + i + j;

	ASSERT_TRUE(matrix1 == matrix2);
	ASSERT_TRUE(matrix2 == matrix1);
	ASSERT_FALSE(matrix1 != matrix2);
	ASSERT_FALSE(matrix2 != matrix1);

	Matrix matrix3 = Matrix(2, 3);

	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix3[i][j] = 1 + i + j;

	ASSERT_TRUE(matrix1 == matrix2);
	ASSERT_TRUE(matrix2 == matrix3);
	ASSERT_TRUE(matrix3 == matrix1);

	ASSERT_FALSE(matrix1 != matrix2);
	ASSERT_FALSE(matrix2 != matrix3);
	ASSERT_FALSE(matrix3 != matrix1);

	matrix1[0][0] = 10;

	ASSERT_FALSE(matrix1 == matrix2);
	ASSERT_FALSE(matrix1 == matrix3);
	ASSERT_TRUE(matrix1 != matrix2);
	ASSERT_TRUE(matrix1 != matrix3);

	Matrix matrix4 = Matrix(2, 4);

	ASSERT_FALSE(matrix1 == matrix4);
	ASSERT_TRUE(matrix1 != matrix4);

	Matrix matrix5 = Matrix(3, 3);

	ASSERT_FALSE(matrix1 == matrix5);
	ASSERT_TRUE(matrix1 != matrix5);

	Matrix matrix6 = Matrix(3, 2);

	ASSERT_FALSE(matrix1 == matrix6);
	ASSERT_TRUE(matrix1 != matrix6);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}