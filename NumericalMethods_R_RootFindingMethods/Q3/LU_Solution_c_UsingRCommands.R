##########Question part 3
a<-matrix(data = NA, nrow = 5, ncol = 5, byrow = FALSE, dimnames = NULL)
n<-nrow(e)
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

source("LUFactorization.R")
# The solution for part c is
x <- lu_f(a,b)

# print("checking the computations PLU = A")
# P%*%(L%*%U)==a

# print("Checking if product of L(inv) and L is identity matrix")
# inv_L%*%L

# print("Checking if product of L(inv) and L is identity matrix")
# inv_U%*%U

# print("Checking if product of L(inv) and L is identity matrix")
# inv_P%*%P

# Printing the solution
print(c("The solution x for the equation Ax = b is: ", x))

print("Quality Checking with the solution of inverse of a with b as x = A(-1)*B")
print(solve(a)%*%b)

print("Quality Checking by multiplying L and U matrices")
print(L%*%U)
