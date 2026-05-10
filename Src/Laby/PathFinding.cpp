#include "PathFinding.h"
#include "lst_co.h"
#include <cmath>
#include <iostream>

/*
void PathFinding::worldToGrid(const gloop::Vector3f& worldPos, float cellSize, int& gridX, int& gridY) {
    gridX = static_cast<int>(worldPos.x / cellSize);
    gridY = static_cast<int>(worldPos.z / cellSize);
}

gloop::Vector3f PathFinding::gridToWorld(int gridX, int gridY, float cellSize) {
    float worldX = (gridX) * cellSize;
    float worldZ = (gridY) * cellSize;
    float worldY = 1.75f;
    
    return gloop::Vector3f(worldX, worldY, worldZ);
}
*/

void PathFinding::worldToGrid(const gloop::Vector3f& worldPos, float cellSize, int& gridX, int& gridY) {
    float x_min = -15.0f; // = -X_SIZE / 2
    float z_min = -15.0f; // = -Z_SIZE / 2

    gridX = static_cast<int>((worldPos.x - x_min) / cellSize);
    gridY = static_cast<int>((worldPos.z - z_min) / cellSize);
}

gloop::Vector3f PathFinding::gridToWorld(int gridX, int gridY, float cellSize) {
    float x_min = -15.0f; // = -X_SIZE / 2
    float z_min = -15.0f; // = -Z_SIZE / 2

    float worldX = x_min + (gridX + 0.5f) * cellSize;
    float worldZ = z_min + (gridY + 0.5f) * cellSize;
    float worldY = 1.75f;

    return gloop::Vector3f(worldX, worldY, worldZ);
}

Lst_co PathFinding::pathfindingIterative(Tab* maze, int startX, int startY) {
    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            maze->cells[y][x].visited = 0;
        }
    }
    
    Lst_co path = new_lst_co(startX, startY);
    Lst_co current = path;
    
    int x = startX;
    int y = startY;
    
    maze->cells[y][x].visited = 1;
    
    while (maze->cells[y][x].type != end) {
        bool found = false;

        //std::cout << "Next target: " << x << ", " << y << std::endl;
        
        if (!found && y + 1 < maze->height && 
            maze->cells[y][x].down && 
            !maze->cells[y + 1][x].visited) {
            y++;
            maze->cells[y][x].visited = 1;
            path = adjt_co(path, x, y);
            found = true;
        }
        
        if (!found && x + 1 < maze->width && 
            maze->cells[y][x].right && 
            !maze->cells[y][x + 1].visited) {
            x++;
            maze->cells[y][x].visited = 1;
            path = adjt_co(path, x, y);
            found = true;
        }
        
        // Essayer d'aller en HAUT
        if (!found && y - 1 >= 0 && 
            maze->cells[y][x].up && 
            !maze->cells[y - 1][x].visited) {
            y--;
            maze->cells[y][x].visited = 1;
            path = adjt_co(path, x, y);
            found = true;
        }
        
        if (!found && x - 1 >= 0 && 
            maze->cells[y][x].left && 
            !maze->cells[y][x - 1].visited) {
            x--;
            maze->cells[y][x].visited = 1;
            path = adjt_co(path, x, y);
            found = true;
        }
        
        if (!found) {
            path = supt_co(path);
            if (path == NULL) {
                return NULL;
            }
            x = path->x;
            y = path->y;
        }
    }
    
    return path;
}

std::vector<gloop::Vector3f> PathFinding::convertPathToWorld(Lst_co path, float cellSize) {
    std::vector<gloop::Vector3f> worldPath;
    
    if (path == NULL) {
        return worldPath;
    }
    
    Lst_co current = path;
    while (current != NULL) {
        gloop::Vector3f worldPos = gridToWorld(current->x, current->y, cellSize);
        worldPath.push_back(worldPos);
        current = current->suiv;
    }
    
    std::reverse(worldPath.begin(), worldPath.end());
    
    return worldPath;
}

std::vector<gloop::Vector3f> PathFinding::findPathToExit(
    Tab* maze,
    const gloop::Vector3f& startWorldPos,
    float cellSize) {
    
    int startGridX, startGridY;
    worldToGrid(startWorldPos, cellSize, startGridX, startGridY);
    
    if (startGridX < 0 || startGridX >= maze->width || 
        startGridY < 0 || startGridY >= maze->height) {
        return std::vector<gloop::Vector3f>();
    }
    
    Lst_co gridPath = pathfindingIterative(maze, startGridX, startGridY);
    
    if (gridPath == NULL) {
        return std::vector<gloop::Vector3f>();
    }
    
    std::vector<gloop::Vector3f> worldPath = convertPathToWorld(gridPath, cellSize);
    
    free_lst_co(gridPath);
    
    return worldPath;
}
