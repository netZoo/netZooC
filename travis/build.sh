#!/bin/bash
cd netZooC/PANDA
make
./PANDA -e ../../tests/ToyData/ToyExpressionData.txt -m ../../tests/ToyData/ToyMotifData.txt -p ../../tests/ToyData/ToyPPIData.txt -a 0.25 -o ToyOutput
cd ../PUMA
./PUMA -e ../../tests/puma/ToyExpressionData.txt -m ../../tests/puma/ToyMotifData.txt -u ../../tests/puma/ToyMiRList.txt -o ToyOutput

