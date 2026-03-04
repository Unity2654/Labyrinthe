#! /bin/sh

mkdir Temp >/dev/null 2>/dev/null
cd Temp
if !(test -f MakeFile && test ../CMakeList.txt -nt MakeFile);
then
	cmake ..;
fi
make
cd ..

mkdir Bin >/dev/null 2>/dev/null
cp Temp/Labyrinthe Bin

Bin/Labyrinthe
