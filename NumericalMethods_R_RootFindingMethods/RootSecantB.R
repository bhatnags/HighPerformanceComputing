
##############SecantMethod############


#Define the function
f<- function (x){
  (exp(x))-2
} 

#Calling the source code
source("SecantMethod.R")
"#Defining values as

a<-0 (lower limit)
b<-1 (upper limit)
eps<- 10^(-6) (required precision)
n<- 10 (iterations)

"
alpha<-log(2) #The exact solution

#SecantMethod(f,a,b,eps,n)
SecantMethod(f,0,1,1e-10,7)
