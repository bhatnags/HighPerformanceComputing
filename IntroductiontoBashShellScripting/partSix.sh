clear

echo "Shell program to take a directory name and count the number of subdirectories, the number of bash scripts, and files"

current_dir=$(pwd)
script_dir=$(dirname $0)

echo $current_dir
echo $script_dir

echo "The number of sub directories"
count_dir=$(find .. -maxdepth 1 -type d|wc -l)
echo $count_dir

echo "The number of files"
count=$(find .. -maxdepth 1 -type f|wc -l)
echo $count

echo "The number of bash scripts"
count=$(find .. -maxdepth 1 -type f -name "*.sh"|wc -l)
echo $count



