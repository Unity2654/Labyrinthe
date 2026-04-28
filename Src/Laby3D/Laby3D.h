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
    Laby3D(Tab t, float x_size, float z_size, float y_size, float wall_thickness, float pillar_width);

    void displayInScene(gloop::Scene &scene);

    const std::vector<gloop::CollisionBox> getMazeCollisionBox() const;

    ~Laby3D();
};
