#!/bin/bash

I_FILES=`ls src/*.i`

for I_FILE in $I_FILES
do
	swig -c++ -lua $I_FILE
done

I_FILES="src/babies.i"

cd src

WRAPPERS=`ls *_wrap.cxx`

g++ -I/usr/include/lua5.1 -c $WRAPPERS

cd ..

ALL_OBJECTS=`ls src/*.o`

g++ -shared -I/usr/include/lua5.1 -L/usr/X11R6/lib64/ -L/usr/lib/lua -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm $ALL_OBJECTS -o babies.so
