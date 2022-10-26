#!/bin/bash

SOURCE_FILES="\
main.cpp \
DataStructs.cpp \
rk4.cpp \
FluxFunctions.cpp \
RHSoperator.cpp"

mpic++ -g -O3 $SOURCE_FILES -Iincludes -o main.p