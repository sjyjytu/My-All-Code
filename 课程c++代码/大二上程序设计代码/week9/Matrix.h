#pragma once
#include <vector>
using namespace std;
class Matrix
{
public:
	Matrix();
	Matrix(int row,int col,vector<int> &values);
	Matrix(int row, int col, vector<vector<int>> &values);
	~Matrix();
	Matrix& operator=(const Matrix& a);
	Matrix operator+(const Matrix& a);
	Matrix operator-(const Matrix& a);
	Matrix operator*(const Matrix& a);
	Matrix T();
	void Print();
private:
	vector<vector<int>> value;
	int Row;
	int Col;
};

