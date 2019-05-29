#!/bin/bash
ls
pwd
cd netzoo-c/panda
pwd
ls
make
./PANDA -e ../../testing/ToyExpressionData.txt -m ../../testing/ToyMotifData.txt -p ../../testing/ToyPPIData.txt -a 0.25 -o ToyOutput
