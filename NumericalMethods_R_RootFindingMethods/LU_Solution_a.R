"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Solution 3(a)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

#Define the first matrix
a <- matrix(c(9, 3, 2, 0, 7,
              7, 6, 9, 6, 4,
              2, 7, 7, 8, 2,
              0, 9, 7, 2, 2,
              7, 3, 6, 4, 3),byrow=T,nrow=5,ncol=5)

# det_a <- det(a)
# print(c("To check if the matrix is singular, determinant of matrix is:", det_a))
# a is a non-singular matrix

#Defining the second matrix to solve the equation AX=B
b <- matrix(c(35, 58, 53, 37, 39),nrow=5,ncol=1)

source("LUFactorization_Revised.R")
# The solution for part a is
x <- lu_f(a,b)

# Printing the solution
x<- round(x,0)
print("The solution x for the equation Ax = b is: ")
print(x)

print("Quality Checking with the solution of inverse of a with b as x = A(-1)*B")
print(solve(a)%*%b)

