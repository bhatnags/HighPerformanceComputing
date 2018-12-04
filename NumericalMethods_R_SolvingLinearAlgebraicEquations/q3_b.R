# R code for the solution of the Initial Value Problem (IVP) using Trapezoid Rule Predictor Corrector method

# Function Trap_rule requires as input:

# - dy.dx: function defining IVP
# Since part one is to be solved
f=function(t,y){-y*log(y)}

# - h: stepsize
n = c(2, 4, 8, 16, 32, 64, 128, 256, 512, 1024)
h=1/n  
l<-length(h)

# - y0: initial value
y0=1/2

# - start: start of the interval
start=0

# - end: end of the interval
end=1

# Define Trapezoid Rule Predictor Corrector method
# Output - y0 is a solution vector, containing values for y(tk) after k=0...nstep iterations

#input t0
t0=1
"Algorithm for the Trapezoid Rule Method:"
trap_rule <- function(f,start,end, h,y0){
    for (k in 1:n){
      f0=f(t0,y0)   # First, predict
      ybar=y0+h*f0
      y=y0+0.5*h*(f0+f(t+h,ybar))   # Next, correct
      y0=y   # Update for next pass through the loop
      t0=t
    }
  y0
}  

"Numerical solution for ODE, Initial Value Problem using Trapezoid Rule order"
ys<-trap_rule(f, start, end, h, y0)
ys

"Clear the environment"
# rm(list=ls())
