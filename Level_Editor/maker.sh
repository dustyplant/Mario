#! /bin/bash

g++ -c Level_Editor.cpp 
mv *.o src/obj
cd src/Entities
g++ -c *.cpp 
mv *.o ../obj
cd ../Units
g++ -c *.cpp 
mv *.o ../obj
cd ../Utilities
g++ -c *.cpp 
mv *.o ../obj
cd ../Level_Structure
g++ -c *.cpp 
mv *.o ../obj
cd ../obj
g++ -o Level_Editor *.o -lSDL -lSDL_image -lSDL_ttf
mv Level_Editor ../..