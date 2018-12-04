
##############BisectionMethod############


#Define the function
f<- function (x){
  (exp(x))-2
} 

#Calling the source code
source("BisectionMethod.R")
"#Defining values as

a<-0 (lower limit)
b<-1 (upper limit)
eps<- 10^(-6) (required precision)
n<- 25 (iterations)

"
#BisectionMethod(f,a,b,eps,n)
BisectionMethod(f, 0, 1, 10^(-6), 25)
