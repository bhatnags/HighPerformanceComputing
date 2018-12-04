#The lu function in R is uses row (partial) pivoting.
"Function lu in R is computing A = PLU, 
which is equivalent to computing the LU decomposition of matrix A 
with its rows permuted by the permutation matrix P(-1): P(-1)A = LU."
#The usage can be seen in the below link:
#  https://cran.r-project.org/web/packages/Matrix/Matrix.pdf
#Run the below command in R for the same
# ?Matrix

#For the same Choleski decomposition can also be used. 
#Consider the command chol(matrix) for using Cholesi decomposition
#?chol


# install the required package
# install.packages("Matrix") 
# access the Matrix library
# library(Matrix)


#Define the matrix for which the LU decomposition with partial pivoting is to be done
lu_f<- function(a,b) {
  
  #Using the "lu" function 
  expand(lu(a))->lua #Initialising all the matrices and saving the result in lua 
  
  #Get the lower, upper & permutation matrix
  lua$L->L #Get the lower matrix
  lua$U-> U #Get the upper matrix
  lua$P-> P #Get the Permutation matrix
  
  #getting inverse of matrices matrix
  solve(L)->inv_L #getting inverse of Lower matrix 
  solve(U)->inv_U #getting inverse of upper matrix
  solve(P)->inv_P #getting inverse of permutation matrix

  #Computing the solution
  #AX = B
  #PLY = B
  #UX = Y
  y = inv_L%*%(inv_P%*%b) #for y
  x = inv_U%*%y #for x
  return(x) #Get the solution X
}



