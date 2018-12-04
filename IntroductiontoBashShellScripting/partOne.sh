clear
echo "Shell program to print all prime numbers between 40000 and 42000"

for((i = 40000; i<= 42000; i++))
 do
 flag=0
 for((j = 2; j<i; j++))
  do
  k=$((i%j))
  if [ $k -eq 0 ];  then
    flag=1
  fi
  done

if [ $flag -eq 0 ]; then
	echo $i
fi


done
