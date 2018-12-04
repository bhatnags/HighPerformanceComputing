#!/bin/bash

clear
echo "Quadratic equation"
read a
read b
read c

echo "~~~~~~~~~~~~~~~~~~~~
for soling quadratic equation ax2 + bx + c = 0, 
x = (-b (+-) sqrt(b^2 -4ac))  / 2a
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
"

ex=$((b*b-4*a*c))

if [ "$ex" -lt 0 ]; then
  echo "Error: the equation has complex solutions"
else
  ex_sq=$(bc <<< "scale=2; sqrt($ex)")
  x1=$(((-b+ex_sq)/(2*a)))
  x2=$(((-b-ex_sq)/(2*a)))
  echo "The two solutions are"
  echo $x1
  echo "and"
  echo $x2
fi


