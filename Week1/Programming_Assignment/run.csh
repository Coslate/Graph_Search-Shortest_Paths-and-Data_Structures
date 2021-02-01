#! /bin/csh -f

make clean
make

#run small testcases
./main ./example.txt -method 1 > answer_loop.log
./main ./example2.txt -method 1 >> answer_loop.log
./main ./example3.txt -method 1 >> answer_loop.log
./main ./example4.txt -method 1 >> answer_loop.log
./main ./example5.txt -method 1 >> answer_loop.log
./main ./example6.txt -method 1 >> answer_loop.log

./main ./example.txt -method 2 > answer_loop2.log
./main ./example2.txt -method 2 >> answer_loop2.log
./main ./example3.txt -method 2 >> answer_loop2.log
./main ./example4.txt -method 2 >> answer_loop2.log
./main ./example5.txt -method 2 >> answer_loop2.log
./main ./example6.txt -method 2 >> answer_loop2.log

#run formal released case
./main ./SCC.txt -method 1
./main ./SCC.txt -method 2
