#pragma once
#include <cstddef>

class Matrix {
	class MatrixProxy {
	public:
		MatrixProxy(size_t row, const Matrix* outer);

		int operator[](const size_t column) const;
		int& operator[](const size_t column);

	private:
		size_t m_row;
		const Matrix* m_outer;
	};

public:
	Matrix(const size_t rows, const size_t columns);

	size_t rows() const;
	size_t columns() const;

	const MatrixProxy operator[](const size_t row) const;
	MatrixProxy operator[](const size_t row);

	Matrix& operator*=(const int num);

	bool operator==(const Matrix& matrix) const;
	bool operator!=(const Matrix& matrix) const;

	~Matrix();

private:
	int** m_matrix = nullptr;
	const size_t m_rows;
	const size_t m_columns;
};