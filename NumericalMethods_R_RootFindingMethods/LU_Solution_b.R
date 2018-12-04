"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Solution 3(b)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#Define the first matrix
a<-matrix(data = NA, nrow = 5, ncol = 5, byrow = FALSE, dimnames = NULL)
n<-nrow(a)
for(i in 1 : n){
  for(j in 1:n){
    a[i,j] = (1/(i+j-1))
  }
}

# det_a <- det(a)
# print(c("To check if the matrix is singular, determinant of matrix is:", det_a))
# a is a non-singular matrix

b <- matrix(c(5.0, 3.550, 2.81428571428571, 2.34642857142857, 2.01746031746032),nrow=5,ncol=1)

source("LUFactorization_Revised.R")
# The solution for part a is
x <- lu_f(a,b)

# Printing the solution
x<- round(x,0)
print("The solution x for the equation Ax = b is: ")
print(x)

print("Quality Checking with the solution of inverse of a with b as x = A(-1)*B")
print(solve(a)%*%b)

