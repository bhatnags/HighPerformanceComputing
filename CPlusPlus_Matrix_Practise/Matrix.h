#include <iostream>

class Matrix{
private:
	int m;
	int n;
	double **p;
	Matrix();

public:
	Matrix(int nrows, int ncols);
	double get(int i_row, int j_col);
	void set(int i_row, int j_col, double val);
	void assign();
	void print();
//	double& operator[](const Matrix& m1);
//	Matrix& operator[](const Matrix& m1);
//	Matrix& operator()(int i_row, int j_col);

	Matrix& operator+ (const Matrix& m1);
	Matrix& operator* (const Matrix& m1);   
	Matrix& operator+= (const Matrix& rhs);
	Matrix& operator- (const Matrix& m1);
	Matrix& operator-= (const Matrix& rhs);
	Matrix& operator*= (const Matrix& T);
	Matrix& operator= (const Matrix& T);
	Matrix transpose(Matrix m);

};
