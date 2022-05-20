#include "Matrix.hpp"

#include <gtest/gtest.h>

class TestMatrix : public ::testing::Test {
};

TEST_F(TestMatrix, zeroShape)
{
	EXPECT_THROW(Matrix matrix = Matrix(0, 0), std::invalid_argument);
	EXPECT_THROW(Matrix matrix = Matrix(0, 1), std::invalid_argument);
	EXPECT_THROW(Matrix matrix = Matrix(1, 0), std::invalid_argument);
}

TEST_F(TestMatrix, bounds)
{
	size_t n = 2;
	size_t m = 3;
	Matrix matrix = Matrix(n, m);

	ASSERT_EQ(matrix.rows(), n);
	ASSERT_EQ(matrix.columns(), m);

	EXPECT_THROW(matrix[0][m], std::out_of_range);
	EXPECT_THROW(matrix[n][0], std::out_of_range);
	EXPECT_THROW(matrix[n][m], std::out_of_range);

	EXPECT_NO_THROW(matrix[0][m - 1]);
	EXPECT_NO_THROW(matrix[n - 1][0]);
	EXPECT_NO_THROW(matrix[n - 1][m - 1]);

	Matrix matrix2 = Matrix(2, 4);
	Matrix matrix3 = Matrix(3, 3);
	Matrix matrix4 = Matrix(3, 2);

	EXPECT_THROW(matrix + matrix2, std::out_of_range);
	EXPECT_THROW(matrix + matrix3, std::out_of_range);
	EXPECT_THROW(matrix + matrix4, std::out_of_range);
}

TEST_F(TestMatrix, bounds1N)
{
	size_t n = 1;
	size_t m = 10;
	Matrix matrix = Matrix(n, m);

	ASSERT_EQ(matrix.rows(), n);
	ASSERT_EQ(matrix.columns(), m);

	EXPECT_THROW(matrix[0][m], std::out_of_range);
	EXPECT_THROW(matrix[n][0], std::out_of_range);
	EXPECT_THROW(matrix[n][m], std::out_of_range);

	EXPECT_NO_THROW(matrix[0][m - 1]);
	EXPECT_NO_THROW(matrix[n - 1][0]);
	EXPECT_NO_THROW(matrix[n - 1][m - 1]);

	Matrix matrix2 = Matrix(n, m - 1);
	Matrix matrix3 = Matrix(n, m + 1);

	EXPECT_THROW(matrix + matrix2, std::out_of_range);
	EXPECT_THROW(matrix + matrix3, std::out_of_range);
}

TEST_F(TestMatrix, boundsN1)
{
	size_t n = 10;
	size_t m = 1;
	Matrix matrix = Matrix(n, m);

	ASSERT_EQ(matrix.rows(), n);
	ASSERT_EQ(matrix.columns(), m);

	EXPECT_THROW(matrix[0][m], std::out_of_range);
	EXPECT_THROW(matrix[n][0], std::out_of_range);
	EXPECT_THROW(matrix[n][m], std::out_of_range);

	EXPECT_NO_THROW(matrix[0][m - 1]);
	EXPECT_NO_THROW(matrix[n - 1][0]);
	EXPECT_NO_THROW(matrix[n - 1][m - 1]);

	Matrix matrix2 = Matrix(n - 1, m);
	Matrix matrix3 = Matrix(n + 1, m);

	EXPECT_THROW(matrix + matrix2, std::out_of_range);
	EXPECT_THROW(matrix + matrix3, std::out_of_range);
}

TEST_F(TestMatrix, bounds11)
{
	size_t n = 1;
	size_t m = 1;
	Matrix matrix = Matrix(n, m);

	ASSERT_EQ(matrix.rows(), n);
	ASSERT_EQ(matrix.columns(), m);

	EXPECT_THROW(matrix[0][m], std::out_of_range);
	EXPECT_THROW(matrix[n][0], std::out_of_range);
	EXPECT_THROW(matrix[n][m], std::out_of_range);

	EXPECT_NO_THROW(matrix[0][m - 1]);
	EXPECT_NO_THROW(matrix[n - 1][0]);
	EXPECT_NO_THROW(matrix[n - 1][m - 1]);

	Matrix matrix2 = Matrix(n + 1, m);
	Matrix matrix3 = Matrix(n, m + 1);
	Matrix matrix4 = Matrix(n + 1, m + 1);

	EXPECT_THROW(matrix + matrix2, std::out_of_range);
	EXPECT_THROW(matrix + matrix3, std::out_of_range);
	EXPECT_THROW(matrix + matrix4, std::out_of_range);
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

TEST_F(TestMatrix, addition)
{
	Matrix matrix1 = Matrix(3, 4);
	Matrix matrix2 = Matrix(3, 4);

	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 4; ++j) {
			matrix1[i][j] = 1 + i + j;
			matrix2[i][j] = -1 * matrix1[i][j];
		}

	Matrix matrix3 = matrix1 + matrix2;
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 4; ++j)
			ASSERT_EQ(matrix3[i][j], 0);

	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 4; ++j) {
			matrix1[i][j] = 1 + i + j;
			matrix2[i][j] = matrix1[i][j];
		}
	Matrix matrix4 = matrix1 + matrix2;
	matrix1 *= 2;
	ASSERT_TRUE(matrix1 == matrix4);
}

TEST_F(TestMatrix, addition1N)
{
	size_t n = 1;
	size_t m = 10;
	Matrix matrix1 = Matrix(n, m);
	Matrix matrix2 = Matrix(n, m);

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j) {
			matrix1[i][j] = 1 + i + j;
			matrix2[i][j] = -1 * matrix1[i][j];
		}

	Matrix matrix3 = matrix1 + matrix2;
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
			ASSERT_EQ(matrix3[i][j], 0);

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j) {
			matrix1[i][j] = 1 + i + j;
			matrix2[i][j] = matrix1[i][j];
		}
	Matrix matrix4 = matrix1 + matrix2;
	matrix1 *= 2;
	ASSERT_TRUE(matrix1 == matrix4);
}

TEST_F(TestMatrix, additionN1)
{
	size_t n = 10;
	size_t m = 1;
	Matrix matrix1 = Matrix(n, m);
	Matrix matrix2 = Matrix(n, m);

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j) {
			matrix1[i][j] = 1 + i + j;
			matrix2[i][j] = -1 * matrix1[i][j];
		}

	Matrix matrix3 = matrix1 + matrix2;
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
			ASSERT_EQ(matrix3[i][j], 0);

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j) {
			matrix1[i][j] = 1 + i + j;
			matrix2[i][j] = matrix1[i][j];
		}
	Matrix matrix4 = matrix1 + matrix2;
	matrix1 *= 2;
	ASSERT_TRUE(matrix1 == matrix4);
}

TEST_F(TestMatrix, stream)
{
	Matrix matrix = Matrix(2, 3);

	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix[i][j] = 1 + i + j;

	std::stringstream ss;
	ss << matrix;
	std::string s;

	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			ss >> s;
			ASSERT_EQ(s, std::to_string(1 + i + j));
		}
	}
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}