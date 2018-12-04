#include <iostream>
//#include <stdio>
//#include <cmath>

#include "Matrix.h"
//srand(1234);

using namespace std;

int main(){

Matrix first_matrix(3,3);
Matrix second_matrix(3,3);

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl ; 
cout << "Matrix A" << endl ; 
first_matrix.print();
cout << "Matrix B" << endl ;
second_matrix.print();

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl ; 
cout << "test matrix functions" << endl ; 
int i1,i2,i3,i4,j1,j2,j3,j4;
double v1,v2,v3,v4;
i1 = 0; j1 = 0; i2 = 1; j2 = 1; i3 = 1; j3 = 0; i4 = 2; j4 = 1; v1 = 0.9; v2 =5.7; v3 = 11.8; v4 = 2.0;//, v5 = 9.1, v6=7.0;
cout << "test function set" << endl << "Set value of A("<< i1 << "," << j1 << ") to " << v1
		<< endl << "Set value of A("<< i2 << "," << j2 << ") to " << v2
		<< endl << "Set value of A("<< i3 << "," << j3 << ") to " << v3
		<< endl << "Set value of A("<< i4 << "," << j4 << ") to " << v4 << endl;
first_matrix.set(i1,j1,v1);
first_matrix.set(i2,j2,v2);
first_matrix.set(i3,j3,v3);
first_matrix.set(i4,j4,v4);
first_matrix.print();
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl ; 
double x = first_matrix.get(i1,j1);
cout << "test function get" << endl << "Get value at A(" << i1 << "," << j1 << ") is " << x << endl;
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl ; 
/*cout << "Using overloading []" << endl << "Set value of A("<< i1 << "," << j1 << ") to " << v5;
second_matrix[i1][j1] = v5;
second_martix.print();
cout << "Using overloading ()" << endl ;
second_matrix(i2,j2) = v6;
second_martix.print();
*/

cout << "assign matrix B for successully assessing operators" << endl;
second_matrix.assign();
cout << "assigned matrix B is" << endl;
second_matrix.print();

cout << "test function operators" << endl;
cout << "+ operator" << endl;
 cout << "\nA = (B * A)\n";
   first_matrix = (second_matrix * first_matrix);
   first_matrix.print();

   cout << "A = A + B\n";
   first_matrix = first_matrix + second_matrix;
   first_matrix.print();
   
   cout << "\nB += A\n";
   second_matrix += first_matrix;
   second_matrix.print();

    cout << "\nA = A - B\n";
   first_matrix = first_matrix - second_matrix;
   first_matrix.print();
   
   cout << "\nB -= A\n";
   second_matrix -= first_matrix;
   second_matrix.print();
   
   if(second_matrix.get(i1,j1) == first_matrix.get(i1,j1)){
	cout<< "Checked with operator '==' the elements are equal\n";
}else if(second_matrix.get(i1,j1) != first_matrix.get(i1,j1)){
	cout << "Checked with operator '!=' the elements are not equal\n";
}
//cout<< "Test transpose function" << endl;
//	transpose(first_matrix).print();


}
