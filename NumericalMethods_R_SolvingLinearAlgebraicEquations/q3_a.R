# R code for the solution of the Initial Value Problem (IVP) using Euler's method

# Function Euler requires as input:
# - dy.dx: function defining IVP
# Varies with the problem statement, defined later

# - h: stepsize, h*nsteps=(end-start)
n = c(2, 4, 8, 16, 32, 64, 128, 256, 512, 1024)
h=1/n  

# - y0: initial value
# Varies with the problem statement, defined later

# - start: start of the interval
start=0

# - end: end of the interval
end=1

# Define Euler;s method
# Output - ys is a solution vector, containing values for y(tk) after k=0...nstep iterations
euler<-function(dy.dx=function(x,y){},start,end, h,y0){
  nsteps <- (end-start)/h
  ys <- numeric(nsteps+1)
  ys[1] <- y0
  for (i in 1:nsteps) {
    x <- start + (i-1)*h
    ys[i+1] <- ys[i] + h*dy.dx(x,ys[i])
  }
  ys
}

# Analytical solution for file in text format 
a <- function(h){
  for(i in 1:10){
  ys <- data.frame(h[i],euler(dy.dx, start=0, end=1, h[i], y0))
  }
  return(ys)
}

"~~~~~~~~~~~~~~~~~~~~~~~~~~Define function for first IVP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

y0=1/2
dy.dx=function(x,y){-y*log(y)}
# Print the solution
a(h)

"~~~~~~~~~~~~~~~~~~~~~~~~~~Define function for second IVP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

y0=1
dy.dx=function(x,y){(1-4*y)}
# Print the solution
a(h)


"~~~~~~~~~~~~~~~~~~~~~~~~~~Define function for third IVP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

y0=1
dy.dx=function(x,y){(y)}
# Print the solution
a(h)

"Clear the environment"
# rm(list=ls())
