#! /bin/csh -f

make clean
make


#run formal released case
./main ./Median.txt > ./test.ans.rerun.log
