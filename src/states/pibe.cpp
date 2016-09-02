#include "pibe.hpp"

static
void do_nothing(double const dt) {
	if (dt != 0) do_nothing(0);
}

void Pibe::update(const float dt) {
	do_nothing(dt);

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

