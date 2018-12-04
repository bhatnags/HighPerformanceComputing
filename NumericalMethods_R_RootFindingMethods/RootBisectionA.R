
##############BisectionMethod############


#Define the function
f<- function (x){
  (x^3)-2
} 

#Calling the source code
source("BisectionMethod.R")
"#Defining values as

a<-0 (lower limit)
b<-2 (upper limit)
eps<- 10^(-6) (required precision)
n<- 25 (iterations)

"
BisectionMethod(f, 0, 2, 10^(-6), 25)
