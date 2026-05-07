#include "Laby3D.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Wall.h"
#include "Pillar.h"
#include "EndDoor.h"
#include "Ground.h"
#include "../GlOOPLib/Scenes/Scenes.h"
#include "../Laby/tab.h"
#include "../Laby/generation.h"

Laby3D::Laby3D(Tab t, float x_size, float z_size, float y_size, float wall_thickness, float pillar_width)
    : t(t),
      x_size(x_size),
      z_size(z_size),
      y_size(y_size),
      wall_thickness(wall_thickness),
      pillar_width(pillar_width){
    generate(t, 1, 1, 1);
    maze_show(t);
}



void Laby3D::displayInScene(gloop::Scene &scene)
{
    scene.addObject(Ground(x_size, z_size));

    float size_cell_x = x_size / t.width;
    float size_cell_z = z_size / t.height;

    float x_min = -x_size / 2;
    float z_min = -z_size / 2;

    float wall_width = size_cell_z - pillar_width;

    for (int i = 0; i < t.height; i++)
    {
        for (int j = 0; j < t.width; j++)
        {
            if (j == 0 && !t.cells[i][j].left)
            {
                auto wall = Wall(x_min,
                    z_min + size_cell_z * i + size_cell_z / 2,
                    wall_width,
                    wall_thickness,
                    y_size,
                    90);
                scene.addObject(wall);
                objectsHitBoxes.push_back(wall.getCollisionBox());

                if (t.cells[i][j].type == end && t.endDoorDirection == LEFT)
                {
                    auto endDoor = EndDoor(x_min, z_min + size_cell_z * i + size_cell_z / 2, y_size*0.75f, size_cell_x*0.65f, 90, scene);
                    scene.addObject(endDoor);
                    objectsHitBoxes.push_back(endDoor.getCollisionBox());

                    std::cout << "end door at left wall, cell (" << j << "," << i << ")" << std::endl;
                }
            }

            if (i == 0 && !t.cells[i][j].up)
            {
                auto wall = Wall(x_min + size_cell_x * j + size_cell_x / 2,
                    z_min,
                    wall_width,
                    wall_thickness,
                    y_size,
                    0);
                scene.addObject(wall);
                objectsHitBoxes.push_back(wall.getCollisionBox());

                if (t.cells[i][j].type == end && t.endDoorDirection == UP)
                {
                    auto endDoor = EndDoor(x_min + size_cell_x * j + size_cell_x / 2, z_min, y_size*0.75f, size_cell_x*0.65f, 0, scene);
                    scene.addObject(endDoor);
                    objectsHitBoxes.push_back(endDoor.getCollisionBox());
                    std::cout << "end door at up wall, cell (" << j << "," << i << ")" << std::endl;
                }
            }

            if (!t.cells[i][j].down)
            {
                auto wall = Wall(x_min + size_cell_x * j + size_cell_x / 2,
                    z_min + size_cell_z * (i + 1),
                    wall_width,
                    wall_thickness,
                    y_size,
                    180);
                scene.addObject(wall);
                objectsHitBoxes.push_back(wall.getCollisionBox());

                if (t.cells[i][j].type == end && t.endDoorDirection == DOWN)
                {
                    auto endDoor = EndDoor(x_min + size_cell_x * j + size_cell_x / 2, z_min + size_cell_z * (i + 1), y_size*0.75f, size_cell_x*0.65f, 180, scene);
                    scene.addObject(endDoor);
                    objectsHitBoxes.push_back(endDoor.getCollisionBox());
                    std::cout << "end door at down wall, cell (" << j << "," << i << ")" << std::endl;
                }
            }

            if (!t.cells[i][j].right)
            {
                auto wall = Wall(x_min + size_cell_x * (j + 1),
                    z_min + size_cell_z * i + size_cell_z / 2,
                    wall_width,
                    wall_thickness,
                    y_size,
                    270);
                scene.addObject(wall);
                objectsHitBoxes.push_back(wall.getCollisionBox());

                if (t.cells[i][j].type == end && t.endDoorDirection == RIGHT)
                {
                    auto endDoor = EndDoor(x_min + size_cell_x * (j + 1), z_min + size_cell_z * i + size_cell_z / 2, y_size*0.75f, size_cell_x*0.65f, 270, scene);
                    scene.addObject(endDoor);
                    objectsHitBoxes.push_back(endDoor.getCollisionBox());
                    std::cout << "end door at right wall, cell (" << j << "," << i << ")" << std::endl;
                }
            }
        }
    }

    float color_pillars[] = {0.0f, 0.0f, 1.0f, 1.0f};
    // draw connection between walls
    for (int i = 0; i < t.height + 1; i++)
    {
        for (int j = 0; j < t.width + 1; j++)
        {

            glPushMatrix();
            glTranslatef(x_min + size_cell_x * j, y_size / 2, z_min + size_cell_z * i);
            glScalef(pillar_width, z_size, pillar_width);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_pillars);
            glutSolidCube(1.0);
            glPopMatrix();
            auto pillar = Pillar(x_min + size_cell_x * j, z_min + size_cell_z * i, pillar_width, y_size);
            scene.addObject(pillar);
            objectsHitBoxes.push_back(pillar.getCollisionBox());
        }
    }
}

const std::vector<gloop::CollisionBox> Laby3D::getMazeCollisionBox() const{
    return objectsHitBoxes;
}

void Laby3D::free()
{
    free_tab(t);
}
