clear
echo "Shell program to take a file and compress it with the following compression utilities"
read a

echo $a
echo echo aa
echo "zip"
zip Hamlet.zip Hamlet.txt
#Hamlet file stays

echo "gzip"
gzip Hamlet.txt
#doesn't stay

echo "bzip2"
bzip2 Hamlet.txt.bz2 Hamlet.txx
#doesn't stay

echo "xz"
tar cfJ Hamlet.tar.xz Hamlet.txt
#Hamlet file stays

echo "Sample report of the different compression file sizes & compression rate"



