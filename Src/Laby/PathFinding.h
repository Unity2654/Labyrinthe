#pragma once

#include "tab.h"
#include "../GlOOPLib/Maths/Vector.h"
#include <vector>
#include <algorithm>
#include "lst_co.h"
#include <stdlib.h>



class PathFinding {
public:
    static std::vector<gloop::Vector3f> findPathToExit(
        Tab* maze,
        const gloop::Vector3f& playerPos,
        float cellSize
    );

private:
    static void worldToGrid(const gloop::Vector3f& worldPos, float cellSize, int& gridX, int& gridY);

    static gloop::Vector3f gridToWorld(int gridX, int gridY, float cellSize);
    
    static Lst_co pathfindingIterative(Tab* maze, int startX, int startY);
    
    static std::vector<gloop::Vector3f> convertPathToWorld(Lst_co path, float cellSize);
};