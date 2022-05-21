#!/bin/bash
gcc -c assembler.c -o ./assembler.o
gcc -c parser.c -o ./parser.o
gcc -c lexer.c -o ./lexer.o
gcc -c linker.c -o ./linker.o
gcc -c output.c -o ./output.o
gcc ./assembler.o ./parser.o ./lexer.o ./linker.o ./output.o -o ./../../tt_asm 
rm *.o