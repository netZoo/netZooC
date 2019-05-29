#!/bin/bash
cd netzoo-c/panda
make
./PANDA -e ../../tests/ToyData/ToyExpressionData.txt -m ../../tests/ToyData/ToyMotifData.txt -p ../../tests/ToyData/ToyPPIData.txt -a 0.25 -o ToyOutput
