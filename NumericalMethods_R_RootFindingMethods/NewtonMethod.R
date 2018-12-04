" Note: other implementation of num. derivative is possible (e.g. backward, symmetric or some predefined function
in R could be used)"
# f - user defined function
# a - start of an interval
# b - end of an interval
# h - step used in the numerical integration
# eps - required precision for the root
# n - maximal number of iterations

#Creating a table format for roots
A <- data.frame(n=as.numeric(),
                 x=as.numeric(),
                 a_Minus_x=as.numeric(),
                 log_a_Minus_x=as.numeric(),
                 stringsAsFactors=FALSE)

#Creating the table format for ratio
#Increase the column as per the requirements
ratio <- data.frame(R_at_20=as.numeric(),
                    Modified_R_inc_23=as.numeric(),
                    Modified_R_inc_25=as.numeric(),
                    Modified_R_inc_3=as.numeric(),
                    Modified_R_inc_4=as.numeric(),
                    Modified_R_inc_5=as.numeric(),
                    Modified_R_6=as.numeric(),
                    Modified_R_7=as.numeric(),
                    # Modified_R_a=as.numeric(),
                    # Modified_R_b=as.numeric(),
                    # Modified_R_c=as.numeric(),
                    stringsAsFactors=FALSE)

#Newton Method to find root in a given interval follows
NumDerivative <- function (f, x0,dx) # computing numerical derivative of a function f
{
  (f(x0+dx)-f(x0))/dx
}
NewtonMethod <- function(f, a, b, eps, n) {
  x0 <- a # setting start value to the interval lower bound
  fa <- f(a) # check if a or b are the root of f(x)
  if (fa == 0.0) {
    return(a)
  }
  fb <- f(b)
  if (fb == 0.0) {
    return(b)
  }
  for (k in 1:n) {
    print("Printing the table with the iterations")
    A<-data.frame(rbind(A, c(k,x0,alpha-x0,log10(alpha-x0))))
    print(A)
    
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    #The below command can be used to write the solution data of the table in the required location
    #Semicolon has been used as a delimiter
    
#    write.table(A, file = "F:\\HPC\\NM\\newton.txt",row.names = FALSE, dec = ".", col.names = c("n", "x", "alpha_Minus_x","log_alpha_Minus_x"), sep = ";")
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    
    fprime= NumDerivative(f, x0, dx) # f'(x0)
    x1 = x0 - (f(x0) / fprime) # calculate next value x1
    
    print("Printing Ratio at p=2 and Modified Ratio at p = 2.3, 2.5, 3, 4, 5, 6, 7")
    print(rbind(ratio, c(
      ((alpha-x1)/(alpha-x0)**2),
      ((alpha-x1)/(alpha-x0)**(2.3)),
      ((alpha-x1)/(alpha-x0)**2.5),
      ((alpha-x1)/(alpha-x0)**3),
      ((alpha-x1)/(alpha-x0)**4),
      ((alpha-x1)/(alpha-x0)**5),
      ((alpha-x1)/(alpha-x0)**6),
      ((alpha-x1)/(alpha-x0)**7)
    )))
    ratio<-data.frame(rbind(ratio,c(
      ((alpha-x1)/(alpha-x0)**2),
      ((alpha-x1)/(alpha-x0)**(2.3)),
      ((alpha-x1)/(alpha-x0)**2.5),
      ((alpha-x1)/(alpha-x0)**3),
      ((alpha-x1)/(alpha-x0)**4),
      ((alpha-x1)/(alpha-x0)**5),
      ((alpha-x1)/(alpha-x0)**6),
      ((alpha-x1)/(alpha-x0)**7)
    )))

"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    #The below command can be used to write the ratio iteration data in the required location
    #Semicolon has been used as a delimiter
    
    
    # write.table(ratio, file = "F:\\HPC\\NM\\data_ratio.txt",row.names = FALSE, dec = ".",
    #             col.names = c("R at p=2.0", "Modified_R at p=2.3", "Modified_R at p=2.5",
    #                           "Modified_R at p=3", "Modified_R at p=4", "Modified_R at p=5",
    #                           "Modified_R at p=6", "Modified_R at p=7"), sep = ";")
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    
    
    if (abs(x1 - x0) < eps) { # check if required precision reached
      print('The found root on the interval [a,b] is:')
      return(x1)
    }
    
    x0 = x1 #continue Newton's method until convergence or max #iter. reached
  }
  print('Maximal number of iterations reached and solution not yet found.')
}

