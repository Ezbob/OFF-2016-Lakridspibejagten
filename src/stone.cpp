#include <iostream>
#include "stone.hpp"
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

void Stone::update(const float dt) {
	if (x() < 0) {
		int pos = 800 + (rand()%200);
		setX(pos); // random pos in range [800,1000)
		std::cerr << "new pos: " << pos << std::endl;
	}

	shape.move(velocity);
}

void Stone::setVelocity(float vx, float vy) {
	velocity.x = vx;
	velocity.y = vy;
}
