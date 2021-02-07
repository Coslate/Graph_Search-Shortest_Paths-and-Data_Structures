#! /bin/csh -f

make clean
make


#run formal released case
./main ./dijkstraData.txt > answer.naive.rerun.log
#> tkdiff ./answer.naive.log ./answer.naive.rerun.log to see the difference.
