#!/bin/bash
cd src/assembler
./build.sh
cd ../..
cd src/interpeter
./build.sh
cd ../..
./tt_asm example.tt
./tt_int outputfile.sef