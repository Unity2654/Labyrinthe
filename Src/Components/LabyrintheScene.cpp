#include "LabyrintheScene.h"
#include "../Laby/tab.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"

LabyrintheScene::LabyrintheScene()
	:	laby(tab_start(WIDTH, HEIGHT, false), X_SIZE, Z_SIZE, Y_SIZE, WALL_THICKNESS, PILLAR_WIDTH) {
	laby.displayInScene(*this);
}
