#pragma once
#include "../GlOOPLib/Objects/Object3D.h"
#include "../GlOOPLib/Scenes/Scenes.h"
#include "../Laby/tab.h"
#include <vector>
#include <memory>
#include "../GlOOPLib/Physics/Collidable.h"

class Laby3D // construct the 3D model of the maze in the scene
{
private:
    Tab t;                // maze 2D
    float x_size;         // size of the maze in x axis
    float z_size;         // size of the maze in z axis
    float y_size;         // size of the maze in y axis
    float wall_thickness; // width of the walls
    float pillar_width;   // height of the walls

    std::vector<gloop::CollisionBox> objectsHitBoxes = {};

public:
    /**
     * @brief Construct a new Laby3D object, with the given parameters
     * @param t The 2D maze to convert in 3D
     * @param x_size The size of the maze on the X axis
     * @param z_size The size of the maze on the Z axis
     * @param y_size The size of the maze on the Y axis
     * @param wall_thickness The thickness of the walls
     * @param pillar_width The width of the pillars at the intersection of the walls
     */
    Laby3D(Tab t, float x_size, float z_size, float y_size, float wall_thickness, float pillar_width);

    /**
     * @brief Display the 3D maze in the scene
     * @param scene The scene in which the maze is displayed
     */
    void displayInScene(gloop::Scene &scene);

    /**
     * @brief Get the collision boxes of the maze
     * @return The collision boxes of the maze
     */
    const std::vector<gloop::CollisionBox> getMazeCollisionBox() const;
    
    // Free the memory related to the object
    // /!\ this leaves the object in an invalid state
    void free();
};
