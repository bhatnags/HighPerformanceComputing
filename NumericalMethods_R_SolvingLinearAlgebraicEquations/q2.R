# R code for the algorithm to solve system of equations Ax=b using Jacobi and Gauss-Seidel iterative solver

"~~~~~~~~~~~~~~~~~~ Input ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
# - A is an n x n nonsingular matrix
"Define matrix a"
a<-matrix(data = NA, nrow = 16, ncol = 16, byrow = FALSE, dimnames = NULL)
n<-nrow(a)
for(i in 1:n){
  for(j in 1:n){
    if (i == j) {
      a[i,j] <- 4
    } else if(i-j == 1){
      a[i,j] = 1
    } else if(i-j ==-1){
      a[i,j] = 1
    } else if(i-j == 4){
      a[i,j] = 1
    } else if(i-j ==-4){
      a[i,j] = 1
    } else {
      a[i,j] = 0
    }
  }
}

# - b is an n x 1 matrix (solution vector)
"Define matrix b"
b = matrix(c(5, 11, 18, 21, 29, 40, 48, 48, 57, 72, 80, 76, 69, 87, 94, 85), nrow = 16, ncol = 1)


# - p is an n x 1 matrix (the initial guess)
p <- matrix( rep( 0, len=n), nrow = n)
xp <- matrix( rep( 0, len=n), nrow = n)

# - epsilon is the tolerance for the solution P
epsilon = 1e-6

# - max1 is the maximum number of iterations
max1 = 100

# Output - x is an n x 1 matrix: the Jacobi approximation to
# the solution of Ax = b

#Define norm vector, taking the max
norm_vec_infty <- function(x) {
  max(x)
}

"~~~~~~~~~~~~~~~~~~~~~~~~Algorithms~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

"Algorithm for Jacobi Iteration"
jacobi <- function(a, b, p, xp, epsilon, max1){
  for (k in 1:max1){
  p=xp;
  for (j in 1:n){
    xp[j]=p[j]+(b[j]-a[j,]%*%p)/a[j,j]
  }
  err=abs(norm_vec_infty(xp-p))
  relerr=err/(abs(norm_vec_infty(xp)))
  if (err<epsilon) {#(relerr<epsilon)
    break;
  }
  }
x=xp
return(x)
}


"Algorithm for Gauss Seidel Iteration"
gauss_siedel <- function(a, b, p, xp, epsilon, max1){
  for (k in 1:max1){
    p=xp;
    for (j in 1:n)
    for (i in 1:j-1){
      xp[j]=p[j]+(b[j]-a[j,]%*%p)/a[j,j]
    }
    for (i in j+1:n){
      xp[j]=p[j]+(b[j]-a[j,]%*%p)/a[j,j]
    }
    err=abs(norm_vec_infty(xp-p))
    relerr=err/(abs(norm_vec_infty(xp)))
    if (err<epsilon) {#(relerr<epsilon)
      break;
    }
  }
  x=xp
  return(x)
}

"~~~~~~~~~~~~~~~~~~~~~~~~~~Numerical Solutions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
j<-jacobi(a, b, p, xp, epsilon, max1)
j

g<-gauss_siedel(a, b, p, xp, epsilon, max1)
g

"Clear the environment"
# rm(list=ls())
