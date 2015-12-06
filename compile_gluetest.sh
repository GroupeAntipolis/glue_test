#!/bin/bash

#Compilation des sources en fichiers objets
g++  -MMD main.cpp -O3 -Iinclude -Iobj/Release/prec/Release  -c -o main.o

#Génération du binaire "gluetest" depuis les fichiers objets.
g++ -o bin/Release/gluetest main.o  libglue/libglue.a libglue/libSmartDataCPP.a libglue/librng.a -lpthread

chmod  755 bin/Release/gluetest



