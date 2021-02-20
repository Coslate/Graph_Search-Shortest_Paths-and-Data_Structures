#! /bin/csh -f

make clean
make


#run formal released case
./main ./algo1-programming_prob-2sum.txt > ./test.ans.log
