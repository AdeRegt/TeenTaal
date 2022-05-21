#!/bin/bash
gcc -c assembler.c -o ./assembler.o
gcc -c parser.c -o ./parser.o
gcc -c lexer.c -o ./lexer.o
gcc ./assembler.o ./parser.o ./lexer.o -o ./../../assembler 
rm *.o