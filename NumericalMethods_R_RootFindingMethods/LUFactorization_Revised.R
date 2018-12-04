#The lu function in R is uses row (partial) pivoting.
"Row pivoting is done by adding an augmented Identity matrix of same size
The pivoting result of the matrix thusly formed can be broken into two matrices of equal size.
The left side will give the Upper matrix.
The right side will give the inverse of Lower matrix.
Computing A = LU, 
For the solution:
Ax = B => LUx = B => x =  U(-1) [{ L(-1) B}]"
#The pseudo code has been taken from the below link:
#  https://www-old.math.gatech.edu/academic/courses/core/math2601/Web-notes/2num.pdf
# input matrix must be square!
# input matrix must be non-singular



#Define the matrix for which the LU decomposition with partial pivoting is to be done
lu_f <- function(a,b){ #Giving the input matrices for which the solution is to be computed
  
  r <- nrow(a) # Rows of the matrix
  c <- ncol(a) # Rows of the matrix  = Columns of the matrix
  
  matrix_aug <- cbind(a, diag(r)) # Augmented matrix: keeping rows same and doubling with Identity matrix with number of columns
  r_aug <- nrow(matrix_aug) # Rows of augmented matrix
  c_aug <- ncol(matrix_aug) # Columns of augmented matrix
  
  for(j in 1:r){
    "~~~~~~~~~~~~~~~~~~~~~~~~~Matrix pivoting starts~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    
    matrix_pivot <- diag(r) #Creating a diagonal matrix
    matrix_pivot[j,j] <- 1/matrix_aug[j,j] # Inserting diagonal values as inverse, so then multiplication becomes 1
    matrix_aug <- matrix_pivot %*% matrix_aug 
    
    if(j == r){                        # no row beneath a[r,r], thus termination
      break()
    }
    
    for(i in (j+1):r){
      matrix_pivot[i,j] <- -matrix_aug[i,j] # Implementation on a[i,j] 
      matrix_aug <- matrix_pivot %*% matrix_aug
    }
    "~~~~~~~~~~~~~~~~~~~~~~~Matrix pivoting ends~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
  }
  
  L <- solve(matrix_aug[,(c+1):c_aug])             # inverse provides L
  U <- matrix_aug[,1:c]
  print("Quality Checking by multiplying L and U matrices")
  QC <- L%*%U
  # QC <- round(QC, 0)
  print(QC)
  print(a)
  
  
  lu_deco <- cbind(L,U)
  
"~~~~~~~~~~~~~~~~~~~Computing solution of Ax = B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ax = B => LUx = B => x =  U(-1) [{ L(-1) B}] ~~~~~~~~~~~~~~~~"

  inv_L <- solve(L)
  # print("Checking if product of L(inv) and L is identity matrix")
  # inv_L%*%L
  
  inv_U <- solve(U)
  # print("Checking if product of L(inv) and L is identity matrix")
  # inv_U%*%U

  x = inv_U%*%(inv_L%*%b) #Get the solution X

  return(x)
}
