" Note: other implementation of num. derivative is possible (e.g. backward, symmetric or some predefined function
in R could be used)"
# f - user defined function
# a - start of an interval
# b - end of an interval
# eps - required precision for the root
# n - maximal number of iterations

#Creating a table format for roots
A <- data.frame(n=as.numeric(),
                x=as.numeric(),
                alpha_Minus_x=as.numeric(),
                stringsAsFactors=FALSE)


#Secant Method to find root in a given interval follows
SecantMethod <- function(f, a, b, eps, n) {
  x0 <- a # setting start value to the interval lower bound
  fa <- f(a) # check if a or b are the root of f(x)
  if (fa == 0.0) {
    return(a)
  }
  x1 <- b
  fb <- f(b)
  if (fb == 0.0) {
    return(b)
  }
  for (k in 1:n) {
    print("Printing the table with the iterations")
    A<-data.frame(rbind(A, c(k,x0,alpha-x0)))
    print(A)
    
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    #The below command can be used to write the data of the table in the required location
    #Semicolon has been used as a delimiter
    
    #   write.table(df, file = "F:\\HPC\\NM\\secant.txt",row.names = FALSE, dec = ".", col.names = c("n", "x", "alpha_Minus_x","log_alpha_Minus_x"), sep = ";")
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    
    f1 <- f(x1)
    f0 <- f(x0)

    x2 = x1 - (f1)*((x1-x0)/(f1-f0))
    f2 <- f(x2)
    x0 <- x1
    x1 <- x2 
    if (abs(x1 - x0) < eps) { # check if required precision reached
      print('The found root on the interval [a,b] is:')
      return(x1)
    }
    
  }
  print('Maximal number of iterations reached and solution not yet found.')
}