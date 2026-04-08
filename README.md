# Labyrinthe

3D movement simulation made with OpenGL 1.1.
Authors : Laura JACQUESON, Dylan MONTENERI, Kilian JELIC. 

## Compile and run

### On linux
Compile the program with ./run.sh. 
The executable will be outputted in the Bin/ directory. CMake build files are outputted in the Temp/ directory.

### On windows
Add all the files in the "{project directory}/Src" directory to Visual Studio, and compile the project to a "{project directory}/Bin" directory, containing glut32.dll. 
Also add the "glut32.ms.lib" to the project.
Be sure the "{project directory}/Resources" directory is present.

The compiled executable will be available in the "{project directory}/Bin" directory.

## How to use 
Rotate the camera with the mouse.
Move with the following keys :
 - Z : Forwards
 - Q : Left
 - S : Backwards
 - D : Right

Toggle Spring by pressing A.

Avoid using directionnal arrow, as they're bugged in the current version.