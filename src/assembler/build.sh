#!/bin/bash
gcc -c assembler.c -o ./assembler.o
gcc -c parser.c -o ./parser.o
gcc ./assembler.o ./parser.o -o ./../../assembler 
rm *.o