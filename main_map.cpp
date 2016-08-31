#include "main_map.h"

MainMap::MainMap(unsigned _x, unsigned _y) {
	loadFromFile("europa.jpg");
	x = _x;
	y = _y;
}

