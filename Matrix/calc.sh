#!/bin/bash
yacc -o matrix.c matrix.y

gcc -c matrix.c -o matrix.o

# -----------------------------------------
#fluid -c iter.fl

# Compile full project
g++ calc.cxx matrix.o -o mat -lm -lfltk -lX11

# Run calculator
./mat

