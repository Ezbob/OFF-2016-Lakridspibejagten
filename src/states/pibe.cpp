#include "pibe.hpp"

void Pibe::update(const float dt) {
	if (x() < 0)
		reset();

	velocity.x -= speed;

	Object::move(velocity);
	sprite.move(velocity);
}

void Pibe::reset() {
	setX(800 + rand()%1600);
}

void Pibe::draw(sf::RenderWindow &window) {
	Object::draw(window);
	window.draw(sprite);
}

