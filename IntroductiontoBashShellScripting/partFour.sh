#!/bin/bash
clear
echo "shell program to run the simple_mc program 100 times with different seeds"

x=0
for run in {1..100}
do
  ./simple_mc $run*100 > ~/Documents/practice/5621/5621_06_bhatnags/null 

  line=$(head -n 1 null)
  if [[ $line = *"(in range of answer 1.333333 ? y)"* ]]; then
    x=$((x+1))
  fi

done
echo "Percentage of time the simple_mc program gave the correct answer"
perc=$(echo "scale=2; $x /100 *100" | bc)
echo $perc "%"
