#! /bin/bash

g++ -g -c Mario.cpp 
mv *.o src/obj

cd src/Entities
g++ -g -c *.cpp 
mv *.o ../obj

cd ../Units
g++ -g -c *.cpp 
mv *.o ../obj
cd Enemies
g++ -g -c *.cpp 
mv *.o ../../obj
cd ../..


cd Utilities
g++ -g -c *.cpp 
mv *.o ../obj

cd ../Level_Structure
g++ -g -c *.cpp 
mv *.o ../obj

cd ../obj
g++ -g -o Mario *.o -lSDL -lSDL_image -lSDL_ttf
mv Mario ../..