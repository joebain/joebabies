#!/bin/bash

I_FILES=`ls src/*.i`

for I_FILE in $I_FILES
do
	swig -c++ -lua $I_FILE
done

cd src

WRAPPERS=`ls *_wrap.cxx`

g++ -I/usr/include/lua5.1 -c $WRAPPERS

cd ..

WRAPPER_OBJECTS=`ls src/*_wrap.o`
ALL_OBJECTS=`ls src/*.o`
SOURCE_OBJECTS=

for OBJECT in $ALL_OBJECTS
do
	if [[ $WRAPPER_OBJECTS != *$OBJECT* ]]
	then
		SOURCE_OBJECTS=$SOURCE_OBJECTS" "$OBJECT
	fi
done

#echo $SOURCE_OBJECTS
#echo $WRAPPER_OBJECTS

g++ -shared -I/usr/include/lua5.1 -L/usr/lib/lua $WRAPPER_OBJECTS $SOURCE_OBJECTS -o babies.so
