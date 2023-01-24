#!/bin/bash
gcc -c add.c
if [ $? -ne 0 ]
then
	read a
fi
gcc -c topic.c
if [ $? -ne 0 ]
then
	read a
fi
gcc -c usage.c
if [ $? -ne 0 ]
then
	read a
fi
gcc -c finish.c
if [ $? -ne 0 ]
then
	read a
fi
gcc -c volume.c
if [$? -ne 0]
then
	read a
fi
gcc -c area.c
if [$? -ne 0]
then
	read a
fi
gcc -c convex.c
if [$? -ne 0]
then
	read a
fi
gcc -c simple.c
if [$? -ne 0]
then
	read a
fi
gcc -c is.c
if [$? -ne 0]
then
	read a
fi
gcc -c read.c
if [$? -ne 0]
then
	read a
fi
gcc  main.c is.o area.o add.o convex.o topic.o usage.o finish.o simple.o volume.o read.o -lm -o geom
./geom 
