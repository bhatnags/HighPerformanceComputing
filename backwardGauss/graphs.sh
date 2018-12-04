#!usr/bin/bash


rm sizeSer.dat sizePar.dat threadsSer.dat threadsPar.dat

awk 'NR%2==0' output.dat > cleandata.dat

#sed -i '1s/^/size  threads  serialTime parallelTime\n/' try.dat

awk ' { print $NF=$1 " " $(NF-1) } ' cleandata.dat >>sizeSer.dat
awk ' { print $NF=$1 " " $(NF) } ' cleandata.dat >>sizePar.dat
awk ' { print $NF=$2 " " $(NF-1) } ' cleandata.dat >>threadsSer.dat
awk ' { print  $NF=$2 " " $(NF) } ' cleandata.dat >>threadsPar.dat


gnuplot -persist <<EOFMarker
set multiplot

set title 'Size vs Time taken for Serial and Parallel versions'
set xlabel 'Size'
set ylabel 'Time'

#set legends \
set key top right
set key box
set key 0.01, 100

plot "sizeSer.dat" using 1:2 with lines title 'Serial', "sizePar.dat" using 1:2 with lines title 'Parallel' 
# 1=x, 2=y

unset multiplot

EOFMarker

gnuplot -persist <<EOFMarker
set multiplot

set title 'Threads vs Time taken for Serial and Parallel versions'
set xlabel 'Threads'
set ylabel 'Time'

#set legends \
set key top right
set key box
set key 0.01, 100

plot "threadsSer.dat" using 1:2 with lines title 'Serial', "threadsPar.dat" using 1:2 with lines title 'Parallel' 
# 1=x, 2=y

unset multiplot

EOFMarker

