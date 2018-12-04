# R code for the solution of the Initial Value Problem (IVP) using Runge-Kutta method

# Function RK requires as input:
# - f: function defining IVP
"Solve part (i)"
f=function(t,y){-y*log(y)}

# - h: stepsize
h=1/4  

# - y0: initial value
y0=1/2

# - start: start of the interval
start=0

# - end: end of the interval
end=1

# Define RK method
# Output - y0 is a solution vector, containing values for y(tk) after k=0...nstep iterations

#input t0
t0=1

"Algorithm for the second-order Runge-Kutta:"
rk_second <- function(f,start,end, h,y0){ 
  for (k in 1:n) {
    t=t0+k*h
    v1=f(t0,y0)
    v2=f(t,y0+h*v1)
    y=(h/6.0)*(v1+2.0*(v2))
    y0=y
    t0=t
  }
y0
}

"Algorithm for the fourth-order Runge-Kutta:"
rk_fourth <- function(f,start,end, h,y0){ 
  for (k in 1:n) {
    t=t0+k*h
    t2=t0+0.5*h
    v1=f(t0,y0)
    v2=f(t2,y0+0.5*h*v1)
    v3=f(t2,y0+0.5*h*v2)
    v4=f(t,y0+h*v3)
    y=(h/6.0)*(v1+2.0*(v2+v3)+v4)
    y0=y
    t0=t
  }
y0
}


"Numerical solution for ODE, Initial Value Problem using RK-2nd order"
ys<-rk_second(f, start, end, h, y0)
ys

"Numerical solution for ODE, Initial Value Problem using RK-4th order"
ys<-rk_fourth(f, start, end, h, y0)
ys

"Clear the environment"
# rm(list=ls())
