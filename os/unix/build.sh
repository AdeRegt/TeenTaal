#! /bin/bash
cc -O0 -c dependancies.c -o dependancies.o
cc -O0 -c ../../main.c -o main.o
gcc main.o dependancies.o -o ./teen
rm *.o
./teen ../../dummpdata.teen