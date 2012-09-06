g++ -c Level_Editor.cpp 
move *.o src/Obj_Folder
cd src/Entities
g++ -c *.cpp 
move *.o ../Obj_Folder
cd ../Units
g++ -c *.cpp 
move *.o ../Obj_Folder
cd ../Utilities
g++ -c *.cpp 
move *.o ../Obj_Folder
cd ../Level_Structure
g++ -c *.cpp 
move *.o ../Obj_Folder
cd ../Obj_Folder
g++ -o Level_Editor.exe *.o -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf
move Level_Editor.exe ..
cd ..
move Level_Editor.exe ..
cd ..