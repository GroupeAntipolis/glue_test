#!/bin/bash

# Preparation
mkdir -p bin/Release

# Compilation des sources en fichiers objets
g++  -MMD main.cpp -O3 -Iinclude -Iobj/Release/prec/Release  -c -o main.o

# Generation du binaire "gluetest" depuis les fichiers objets.
g++ -o bin/Release/gluetest main.o  libglue/libglue.a libglue/libSmartDataCPP.a libglue/librng.a -lpthread

# Finalisation
chmod  755 bin/Release/gluetest