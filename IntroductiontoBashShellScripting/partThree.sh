#!/bin/bash

clear
echo "Shell prograsm to print 6 lottery numbers between 1 to 45"
for i in {1..6}
do
  r=$[ ( $RANDOM % 45 ) + 1 ];
  echo $r
done


