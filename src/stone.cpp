#include <iostream>
#include "stone.hpp"
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

void Stone::update(const float dt) {
	if (x() < 0) {
		int pos = 800 + (rand()%200);
		setX(pos); // random pos in range [800,1000)
		//std::cerr << "new pos: " << pos << std::endl;
	}

	sprite.move(velocity);
}

void Stone::scale(float sx, float sy) {
	sprite.setScale({sx, sy});
	width = width * sx;
	height = height * sy;
}

void Stone::setVelocity(float vx, float vy) {
	velocity.x = vx;
	velocity.y = vy;
}
