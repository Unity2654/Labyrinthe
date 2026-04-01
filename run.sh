#! /bin/sh

mkdir Temp >/dev/null 2>/dev/null
cd Temp
if !(test -f MakeFile && test ../CMakeList.txt -nt MakeFile);
then
	if !(cmake ..);
	then
			echo "\nrun : cmake command failed !";
			exit 1;
	fi
fi
if !(make);
then
	echo "\nrun : make command failed !";
	exit 1;
fi
cd ..

mkdir Bin >/dev/null 2>/dev/null
cp Temp/Labyrinthe Bin

clear
cd Bin
./Labyrinthe
