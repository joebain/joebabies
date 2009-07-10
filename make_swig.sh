#!/bin/bash

swig -lua lua/swig/*.i

WRAPPERS=`ls lua/swig/*_wrap.c`

g++ -I/usr/include/lua5.1 -c $WRAPPERS

WRAPPER_OBJECTS=`ls lua/swig/*_wrap.c`
SOURCE_OBJECTS=`ls src/*.o`

g++ -shared -I/usr/include/lua5.1 -L/usr/lib/lua $WRAPPER_OBJECTS $SOURCE_OBJECTS -o rattlesnake.so
