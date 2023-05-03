#!/bin/bash
g++ generator.cpp -o g.exe -std=c++20 -O2 -Wall -Wextra -Wconversion
echo "Generator Compilation Done."
./g.exe
echo "Input Data Generation Done."
g++ validator.cpp -o v.exe -std=c++20 -O2 -Wall -Wextra -Wconversion
echo "Validator Compilation Done."
g++ checker.cpp -o c.exe -std=c++20 -O2 -Wall -Wextra -Wconversion
echo "Checker Compilation Done."
./c.exe B 20
echo "Output Data Generation Done."