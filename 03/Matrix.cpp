#include "Matrix.hpp"

#include <stdexcept>

Matrix::MatrixProxy::MatrixProxy(size_t row, const Matrix* outer)
    : m_row(row)
    , m_outer(outer)
{
}

int Matrix::MatrixProxy::operator[](const size_t column) const
{
	if (column >= m_outer->m_columns)
		throw std::out_of_range("");
	return m_outer->m_matrix[m_row][column];
}

int& Matrix::MatrixProxy::operator[](const size_t column)
{
	if (column >= m_outer->m_columns)
		throw std::out_of_range("");
	return m_outer->m_matrix[m_row][column];
}

Matrix::Matrix(const size_t rows, const size_t columns)
    : m_rows(rows)
    , m_columns(columns)
{
	if (rows == 0 || columns == 0)
		throw std::invalid_argument("");

	m_matrix = new int*[rows];
	for (size_t i = 0; i < rows; i++)
		m_matrix[i] = new int[columns];
}

size_t Matrix::rows() const
{
	return m_rows;
}

size_t Matrix::columns() const
{
	return m_columns;
}

const Matrix::MatrixProxy Matrix::operator[](const size_t row) const
{
	if (row >= m_rows)
		throw std::out_of_range("");
	return (MatrixProxy(row, this));
}

Matrix::MatrixProxy Matrix::operator[](const size_t row)
{
	if (row >= m_rows)
		throw std::out_of_range("");
	return (MatrixProxy(row, this));
}

Matrix& Matrix::operator*=(const int num)
{
	for (size_t i = 0; i < m_rows; i++)
		for (size_t j = 0; j < m_columns; j++)
			m_matrix[i][j] *= num;
	return *this;
}

bool Matrix::operator==(const Matrix& matrix) const
{
	if (m_columns != matrix.columns())
		return false;
	if (m_rows != matrix.rows())
		return false;
	for (size_t i = 0; i < m_rows; i++)
		for (size_t j = 0; j < m_columns; j++)
			if (m_matrix[i][j] != matrix[i][j])
				return false;
	return true;
}

bool Matrix::operator!=(const Matrix& matrix) const
{
	return !(*this == matrix);
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < m_rows; i++)
		delete[] m_matrix[i];
	delete[] m_matrix;
}
