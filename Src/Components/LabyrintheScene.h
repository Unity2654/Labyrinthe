#include "../GlOOPLib/Scenes/Scenes.h"
#include "../Laby3D/Laby3D.h"

// The scene the labyrinthe is displayed in
class LabyrintheScene: public gloop::Scene {
private:

	// Constants for the creation of the maze
	// Allows the use a default constructor for the scene
	static constexpr float X_SIZE = 30.0f;
	static constexpr float Z_SIZE = 30.0f;        // size of the maze in z axis
	static constexpr float Y_SIZE = 4.0f;         // size of the maze in y axis
	static constexpr float WALL_THICKNESS = 0.2f; // width of the walls
	static constexpr float PILLAR_WIDTH = 0.4f;   // width of the pillars*
	// Creation of the 2D tab
	static constexpr int WIDTH = 10;		      
	static constexpr int HEIGHT = 10;

	Laby3D laby;

public:

	LabyrintheScene();

	virtual void display() override;

};