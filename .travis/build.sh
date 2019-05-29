#!/bin/bash
cd netzoo-c/panda
make
./PANDA -e ../../testing/ToyData/ToyExpressionData.txt -m ../../testing/ToyData/ToyMotifData.txt -p ../../testing/ToyData/ToyPPIData.txt -a 0.25 -o ToyOutput
