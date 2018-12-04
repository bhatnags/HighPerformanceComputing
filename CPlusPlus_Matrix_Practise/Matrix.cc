#include <iostream>
#include <cstdlib>
#include "Matrix.h"
#include <time.h>

using namespace std;

//constructor
Matrix::Matrix(int nrows, int ncols) {// rectangular matrix of doubles
	m = nrows; 
	n = ncols; 
	p = new double*[m]; //memory management
	for (int i = 0; i < m; ++i){
		p[i] = new double[n]; //memory management
		for (int j = 0; j < n; ++j)
			p[i][j] = 0.0;
	}
}
/*
double& Matrix::operator[](int m, int n){
	return p[m][n];
}

double Matrix::operator[](int m, int n){
	return p[m][n];
}

//destructor
Matrix::~Matrix(){ 
 for (int i = 0; i < m; ++i){
	for (int j = 0; j < n; ++j){
		delete p[j];
	}
 delete p[i];
 delete p;
}
 */
double Matrix::get(int m, int n){ 
    return p[m][n]; 
}

void Matrix::set(int m, int n, double val){ 
    p[m][n] = val; 
}

void Matrix::assign(){ 
srandom(time(NULL));
 for(int i = 0; i < m; i++){ 
  for(int j = 0; j < n; j++){ 
   p[i][j] = (double)(rand()/10000); 
  } 
 } 
}
 
void Matrix::print(){ 
 cout <<"The matrix is:\n";
 for(int i = 0; i < m; i++){ 
  for(int j = 0; j < n; j++){ 
   cout << p[i][j] <<" "; 
  }
  cout <<endl;
 } 
}
  

Matrix& 
Matrix::operator+(const Matrix& m1){
  return (*this += m1);
}

Matrix& 
Matrix::operator-(const Matrix& m1){
  return (*this -= m1);
}
   
Matrix& 
Matrix::operator* (const Matrix& m1){
 return (*this *= m1);
}
   
Matrix& 
Matrix::operator+= (const Matrix& rhs){
      for(int i = 0; i < m; i++){
	 for(int j = 0; j < n; j++){
	    p[i][j] += rhs.p[i][j]; 
	 } 
      }      
      return *this;
   }
   
Matrix& 
Matrix::operator-= (const Matrix& rhs){
      for(int i = 0; i < m; i++){
	 for(int j = 0; j < n; j++){
	    p[i][j] -= rhs.p[i][j]; 
	 } 
      }      
      return *this;
   }
   
Matrix& 
Matrix::operator*= (const Matrix& T){
      if(n == T.m){
	 for(int i = 0; i < T.m; ++i){
	    for(int k = 0; k < n; ++k){
		 p[i][k] *= T.p[k][i];
	    }
	 }
      }
      
      return *this;
   }
   
Matrix& 
Matrix::operator= (const Matrix& T){
      p = T.p;
      n = T.n;
      m = T.m;
      return *this;
   }


/*Matrix transpose(Matrix m){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			n[j][i] = m[i][j];
		}
	}
	return n;
}*/
