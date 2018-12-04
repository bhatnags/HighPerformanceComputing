
##############NewtonMethod############


#Define the function
f<- function (x){
  (exp(x))-2
} 

#Calling the source code
source("NewtonMethod.R")
"#Defining values as

a<-0 (lower limit)
b<-1 (upper limit)
eps<- 10^(-6) (required precision)
n<- 25 (iterations)

"
dx<-1e-7 #The derivative value
alpha<-log(2) #The exact solution

#NewtonMethod(f,a,b,eps,n)
NewtonMethod(f,0,1,1e-10,6)
