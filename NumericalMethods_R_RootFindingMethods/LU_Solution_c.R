"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Solution 3(c)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
a<-matrix(data = NA, nrow = 5, ncol = 5, byrow = FALSE, dimnames = NULL)
n<-nrow(a)
for(i in 1:n){
  for(j in 1:n){
    if (i == j) {
      a[i,j] <- 1
    } else if(i-j ==1) {
      a[i,j] = 4
    } else if(i-j ==-1) {
      a[i,j] = -4
    } else {
      a[i,j] = 0
    }
  }
}

b <- matrix(c(-4, -7, -6, -5, 16),nrow=5,ncol=1)

source("LUFactorization_Revised.R")
# The solution for part a is
x <- lu_f(a,b)

# Printing the solution
x<- round(x,0)
print("The solution x for the equation Ax = b is: ")
print(x)

print("Quality Checking with the solution of inverse of a with b as x = A(-1)*B")
print(solve(a)%*%b)

