#include <iostream>
#include "stone.hpp"
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

static
void do_nothing(double const dt) {
	if (dt != 0) do_nothing(0);
}

void Stone::draw(sf::RenderWindow &window) {
	Object::draw(window);
	window.draw(sprite);
}

void Stone::update(const float dt) {
	do_nothing(dt);

	if (x() < 0) {
		reset();
	}

	velocity.x -= speed;

	Object::move(velocity);
	sprite.move(velocity);
}

void Stone::reset() {
	// New scale
	float sc = 2.f + (rand()%4)/2.f;
	scale(sc, sc);

	// New position
	int pos = startpos.x + (rand()%200);
	setX(pos); // random pos in range [800,1000)
	setY( ground_levels[rand()%2]-height() );
}

void Stone::scale(float sx, float sy) {
	Object::setScale({sx, sy});
	sprite.setScale({sx, sy});
}

void Stone::setVelocity(float vx, float vy) {
	velocity.x = vx;
	velocity.y = vy;
}
