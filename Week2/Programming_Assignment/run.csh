#! /bin/csh -f

make clean
make


#run formal released case
./main ./dijkstraData.txt > answer.naive.rerun.log
