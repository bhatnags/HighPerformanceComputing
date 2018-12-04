"Condition number of A = (infinity norm of A) x (infinity norm of A_inverse)"
"Matrix infinity norm  = max(sum of row)"

"Function to calculate the Inverse of the matrix using matrix package"
# install the required package
# install.packages("Matrix") 
# access the Matrix library
library(Matrix)

lu_f<- function(a) {
  
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
  
  y = inv_U%*%(inv_L%*%(inv_P)) #for y
  return(y)
  
}

#Assume y
y0 <- list()
for(n in 4:20){
  y0[[n]]<-matrix( rep(100, len=n), nrow = n)
}


"Function to calculate the Infinity norm of a matrix"
inf_norm <- function(a,n){
  t<-t(a) #transpose of a matrix
  m<-max(colSums(t)) #max of row
  return(m)
}

"Function to calculate the infinity norm of inverse of the matrix"
inf_norm_inv <- function(a,n){
  for(i in 1:n){
  y<- ((lu_f(a)%*%y0[[n]])/inf_norm(y0[[n]]))
  y0[[n]]<-y
  }
  inf_norm(y0[[n]])
}

cond_num<- function(a,n){
  kappa <- inf_norm(a,n) * (inf_norm_inv(a,n))
  kappa
}


"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Solution 1(a)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#Define the first matrix
matrices <- list()
for(n in 4:20){ #n is the size of the matrix
  matrices[[n]]<-matrix(data = NA, nrow = n, ncol = n, byrow = FALSE, dimnames = NULL)
  for(i in 1 : n){
    for(j in 1:n){
      matrices[[n]][i,j] = (1/(i+j-1))
    }
  }
}

#Create an empty data frame for plotting and storing the results
table_a<-data.frame(n = as.numeric(), kappa = as.numeric())

  for(n in 4:20){
    a<- matrices[[n]]
    cn <- cond_num(a,n)
    result <- c(n, cn)
    print(result)
    table_a<-rbind(table_a,data.frame(n = n, kappa = cn))
  }
plot(table_a, kappa~n)

"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Solution 1(b)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#Define the second matrix
matrices <- list()
for(n in 4:20){ #n is the size of the matrix
  matrices[[n]]<-matrix(data = NA, nrow = n, ncol = n, byrow = FALSE, dimnames = NULL)
  for(i in 1:n){
    for(j in 1:n){
      if (i == j) {
        matrices[[n]][i,j] <- 1
      } else if(i-j ==1) {
        matrices[[n]][i,j] = 4
      } else if(i-j ==-1) {
        matrices[[n]][i,j] = -4
      } else {
        matrices[[n]][i,j] = 0
      }
    }
  }
  }

table_b<-data.frame(n = as.numeric(), kappa = as.numeric())
    for(n in 4:20){
      a<- matrices[[n]]
      cn <- cond_num(a,n)
      result_b <- c(n, cn)
      print(result_b)
      table_b<-rbind(table_b,data.frame(n = n, kappa = cn))
      }    
plot(table_b, kappa~n)

"Clear the environment"
# rm(list=ls())
