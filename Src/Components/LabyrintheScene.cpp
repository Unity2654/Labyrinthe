#include "LabyrintheScene.h"
#include "../Laby/tab.h"
#include "../Laby3D/Laby3D.h"
#include "../Laby/generation.h"

LabyrintheScene::LabyrintheScene()
	:	laby(tab_start(width, height, false), x_size, z_size, y_size, wall_thickness, pillar_width) {
	laby.displayInScene(*this);
}
