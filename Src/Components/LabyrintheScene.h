#include "../GlOOPLib/Scenes/Scenes.h"
#include "../Laby3D/Laby3D.h"

// The scene the labyrinthe is displayed in
class LabyrintheScene: public gloop::Scene {
private:

	// Constants for the creation of the maze
	// Allows the use a default constructor for the scene
	static constexpr float x_size = 30.0f;
	static constexpr float z_size = 30.0f;        // size of the maze in z axis
	static constexpr float y_size = 4.0f;         // size of the maze in y axis
	static constexpr float wall_thickness = 0.2f; // width of the walls
	static constexpr float pillar_width = 0.4f;   // width of the pillars*
	// Creation of the 2D tab
	static constexpr int width = 10;		      
	static constexpr int height = 10;			  

	Laby3D laby;

public:
	
	LabyrintheScene();

};