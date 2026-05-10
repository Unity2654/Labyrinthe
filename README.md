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
 - Z/↑ : Forwards
 - Q/← : Left
 - S/↓ : Backwards
 - D/→ : Right

Press A to sprint.
Press Space to jump.

Press Esc to return to the menu.
When on the menu, press Esc to leave the game.

## Debug
- F1 : Switches the display between Points mode, Wireframe mode and full mode
- F2 : Toggle lighting
- F3 : Toggle textures
- F4 : Reduce the number of facets used by the objects
- F5 : Increase the number of facets used by the object