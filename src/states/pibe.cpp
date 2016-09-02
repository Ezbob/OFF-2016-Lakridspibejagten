#include "pibe.hpp"

void Pibe::update(const float dt) {
	if (!active)
		return;

	if (x() < 0)
		reset();

	velocity.x -= speed;

	Object::move(velocity);
	sprite.move(velocity);
}

void Pibe::reset() {
	setX(800 + rand()%1600);
	setY(100*(1+rand()%5) );
	active = true;
}

void Pibe::setInactive() {
	active = false;
}

void Pibe::draw(sf::RenderWindow &window) {
	Object::draw(window);
	window.draw(sprite);
}

