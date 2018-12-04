# Bisection method for root-finding
# f - user defined function
# a - start of an interval
# b - end of an interval
# nmax - maximal number of steps in the bisection method (divisions of the interval [a,b])
# eps - required precision for the root

#Creating a table format
A <- data.frame(n=as.numeric(),
                 x=as.numeric(),
                 b_Minus_a=as.numeric(),
                 b=as.numeric(),
                 a=as.numeric(),
                 stringsAsFactors=FALSE)

#Bisection Method to find root in a given interval follows
BisectionMethod <- function(f, a, b, eps, nmax) {
  
  fa <- f(a) # check if a or b are the root of f(x)
  if (fa == 0.0) {
    return(a)
  }
  fb <- f(b)
  if (fb == 0.0) {
    return(b)
  }
  k=1 # iteration nr. counter
  while ((abs(a-b)>eps)&&(k<nmax))
  {
    #Printing the entire sequence of iterates to the files
    k<-k+1  #increase the counter number after every iteration
    print("Printing the table row of current iteration")
    print(c(k,x0,(b-a),b,a))
    print("Printing the table appending the current iteration in the table")
    A<-data.frame(rbind(A, c(k,x0,(b-a),b,a)))
    print(A)
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    #The below command can be used to write the data of the table in the required location
    #Semicolon has been used as a delimiter
    
    #write_location<- write.table(A, file = "F:\\HPC\\NM\\bisection2.txt",row.names = FALSE, dec = ".", col.names = c("n", "x", "b_Minus_a", "b","a"), sep = ";")

"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"    
    x0 <- a+(b-a)/2 # finding midpoint of the interval
    if ((f(a) * f(x0)) < 0)
      b<-x0
    else
      a<-x0
        }

  if (k<nmax) {
    print('The found root on the interval [a,b] is:')
    return(x0)
  }
  else
    print('Maximal number of iterations reached and solution not yet found.')
}
