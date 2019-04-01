#include "Matrix.h"
#include <iostream>


Matrix::Matrix()
{
	throw string("not enough parameter");
}


Matrix::Matrix(int row, int col, vector<int>& values):Row(row),Col(col)
{
	if (row <= 0 || col <= 0)
		throw string("improper parameter given");
	if (values.empty())
		throw string("empty values");
	if (row*col != values.size())
		throw string("row*col!=values.size");
	for (int i = 0; i < row; i++)
	{
		vector<int> tmp;
		for (int j = 0; j < col; j++)
		{
			tmp.push_back(values[i*col + j]);
		}
		value.push_back(tmp);
	}
}

Matrix::Matrix(int row, int col, vector<vector<int>> &values) :Row(row), Col(col)
{
	if (row <= 0 || col <= 0)
		throw string("improper parameter given");
	if (values.empty())
		throw string("empty values");
	if (row*col != values.size()*values[0].size())
		throw string("row*col!=values.size");
	value = values;
}

Matrix::~Matrix()
{
}

Matrix& Matrix::operator=(const Matrix & a)
{
	if (this == &a)
		return *this;
	vector<vector<int>> tmp(a.value);
	this->value = tmp;
	return *this;
}

Matrix Matrix::operator+(const Matrix & a)
{
	if (Row != a.Row || Col != a.Col)
		throw string("Size improper");
	vector<vector<int>> tmp(value);
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
			tmp[i][j] += a.value[i][j];
	return Matrix(Row, Col, tmp);
}

Matrix Matrix::operator-(const Matrix & a)
{
	if (Row != a.Row || Col != a.Col)
		throw string("Size improper");
	vector<vector<int>> tmp(value);
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
			tmp[i][j] -= a.value[i][j];
	return Matrix(Row, Col, tmp);
}

Matrix Matrix::operator*(const Matrix & a)
{
	if (Col != a.Row)
		throw string("Size improper");
	vector<vector<int>> tmp;
	for (int i = 0; i < Row; i++)
	{
		vector<int> tmp2;
		for (int j = 0; j < a.Col; j++)
		{
			int sum = 0;
			for (int k = 0; k < Col; k++)
			{
				sum += value[i][k] * a.value[k][j];
			}
			tmp2.push_back(sum);
		}
		tmp.push_back(tmp2);
	}
	return Matrix(Row, a.Col, tmp);
}

Matrix Matrix::T()
{
	vector<vector<int>>tmp;
	for (int i = 0; i < Col; i++)
	{
		vector<int> tmp2;
		for (int j = 0; j < Row; j++)
		{
			tmp2.push_back(value[j][i]);
		}
		tmp.push_back(tmp2);
	}
	Matrix matrix(Col, Row, tmp);
	return matrix;
}

void Matrix::Print()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
			std::cout << value[i][j] << "  ";
		cout << endl;
	}
}
