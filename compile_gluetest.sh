#!/bin/bash

# Preparation
mkdir -p bin/Release

# Compilation des sources en fichiers objets
g++  -MMD main.cpp -O3 -Iinclude -Iobj/Release/prec/Release  -c -o main.o

# Generation du binaire "gluetest" depuis les fichiers objets.
g++ -o bin/Release/gluetest main.o  libglue/libglue.a libglue/libSmartData.a libglue/librng.a -lpthread

rm main.o
rm main.d

# Finalisation
chmod  755 bin/Release/gluetest
