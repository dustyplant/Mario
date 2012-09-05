g++ -c *.cpp
cd ..
g++ -c *.cpp
mv *.o Level_Editor
cd ../Entities
g++ -c *.cpp
mv *.o ../Level_Structure/Level_Editor
cd ../Utilities
g++ -c *.cpp
mv *.o ../Level_Structure/Level_Editor
cd ../Level_Structure/Level_Editor
g++ -o Level_Editor *.o -lSDL -lSDL_image