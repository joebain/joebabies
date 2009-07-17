#!/bin/bash

I_FILE="src/babies.i"

swig -c++ -lua $I_FILE

cd src

WRAPPERS=`ls *_wrap.cxx`

echo "compiling wrappers"

g++ -I/usr/include/lua5.1 -c $WRAPPERS

cd ..

ALL_OBJECTS=`ls src/*.o`

echo "linking lib"

g++ -shared -I/usr/include/lua5.1 -L/usr/X11R6/lib64/ -L/usr/lib/lua -llua5.1 -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm $ALL_OBJECTS -o babies.so
