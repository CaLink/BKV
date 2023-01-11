#!/bin/bash
yacc -o calcf.c calcf.y

gcc -c calcf.c -o calcf.o

# -----------------------------------------
#fluid -c iter.fl

# Compile full project
g++ func.cxx calcf.o -o func  -lm -lfltk -lX11

# Run calculator
./func

