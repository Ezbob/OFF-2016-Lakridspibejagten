#include "pibe.hpp"

void Pibe::update(const float dt) {
}

void Pibe::draw(sf::RenderWindow &window) {
	Object::draw(window);
	window.draw(sprite);
}

