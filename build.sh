#!/bin/bash
echo ""
echo "Build assembler"
cd src/assembler
./build.sh
cd ../..
echo ""
echo "Build interpeter"
cd src/interpeter
./build.sh
cd ../..

echo ""
echo "Assembler"
./tt_asm example.tt
echo ""
echo "Interpeter"
./tt_int outputfile.sef