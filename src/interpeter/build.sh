#!/bin/bash
gcc -c interpeter.c -o ./interpeter.o
gcc ./interpeter.o -o ./../../tt_int 
rm *.o