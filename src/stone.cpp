#include <iostream>
#include "stone.hpp"
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

void Stone::draw(sf::RenderWindow &window) {
	Object::draw(window);
	window.draw(sprite);
}

void Stone::update(const float dt) {
	if (x() < 0) {
		//std::cerr << "new pos: " << pos << std::endl;
		reset();
	}

	velocity.x += speed;

	Object::move(velocity);
	sprite.move(velocity);
	//rectShape.move(velocity);
}

void Stone::reset() {
	// New scale
	float sc = 1.f + (rand()%4)/2.f;
	scale(sc, sc);

	// New position
	int pos = 800 + (rand()%200);
	setX(pos); // random pos in range [800,1000)
	//rectShape.setPosition({pos, y()});
}

void Stone::scale(float sx, float sy) {
	Object::setScale({sx, sy});
	sprite.setScale({sx, sy});
	//width = width * sx;
	//height = height * sy;
	// Bounding box
	//rectShape.setScale({sx ,sy});
}

void Stone::setVelocity(float vx, float vy) {
	velocity.x = vx;
	velocity.y = vy;
}
