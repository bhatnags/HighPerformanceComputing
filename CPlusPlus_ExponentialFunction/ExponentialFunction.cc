/******************************Assignment 1 for 5614******************/
/********************CPP Program for Exponential function****************/
/************************Author : Saumya Bhatnagar*************************/


#include <iostream>
using namespace std;

long double fact(const int &n){				// function to get the factorial value for n

/*taking "long" to address the last part of first problem "to safeguard your function against calls where it may produce undefined behaviour, for example for very large x" */
	long double val = 1.00000;				
	
	if (n<1){					// throw error for running for negative number
	  cerr << "error\n";
	}else if ((n==1)||(n==2)){
	  val = 1.00000;
	}else{ 
	  val = 2*val;
	  for(int i = 3; i<n ; i++){
	   val *= i;
	  }
	}
return val;
}

long double expo(const double &x, const double &m){	//function to get the exponent values, here x to the power m
	long double val = 1.00000;
	  for(int i=1; i<m; ++i){
	    val *= x;
	    }
	return val;
}


double expo_fact(const double &x){			//function to get the exponential function
	
	float expr = 0.00000;				//assuming initial value of the expression to be zero
	float err = 10.00000;				//let error be huge
	float init;
	double f;

	float eps = 0.000009;				//correct to five significant digits
	  init = 0.00000;
	  for(int i = 1;  ; i++){ 			//infinite loop to get the sum 
	
	   if (err > eps){				//till the error is less that the required precision
	    init = expr;
//	    cout << "\nno of iteration is " << i << "\nfact is " << fact(i) << endl << "expo is " << expo(x, i) << endl;
//	    cout << "expr is " << expr << endl;

	    expr += (expo( x, i)/fact(i));		//summing every term of the expression, a += b => a=a+b 

	    err = expr>init ? (expr-init) : (init-expr);//saving the difference between two terms in err (error)
//	    cout << "expr is " << expr << "\nerror is " << err << "\ninit is "<< init << endl;
	  } else {
		break;					//break the condition
	  }
	 }	
	return expr;
}

double expr_sq(const double &x){ 			// function to get the exponential function using division formula
	double val; 
	if(x > 0.5){
	val = (expr_sq(x/2))*(expr_sq(x/2));
	} else if(x < -0.5){
	val = (expr_sq(x/2))*(expr_sq(x/2));
	} else{
	val = expo_fact(x);	
	}
	return val;
}

int main(){ 						// demonstrating the required calls

cout << "\n************************Printing Part 1**********************" << endl;
for(int x = 0; x< 5 ; x++){
	double y = (double) x/10;
	double a = expo_fact(y);
	cout << "for x = " << y << " : expression sum = " << a << endl;
	}

cout << "\n**********************Printing Part 2********************************" << endl;
for(int x = 0; x< 51; x++){
	double y = (double)x;
	double a = expr_sq(y);
	cout << "for x = " << y << " : expression sum = " << a << endl;
}

cout << "\n*********************Printing Part 3******************************" << endl;
	for(int i = -50; i< 51; i++){
	double y = (double)i;
	cout << "for x = " << i << " : expression sum = " << expr_sq(y) << endl;
	}



return 0;
}

