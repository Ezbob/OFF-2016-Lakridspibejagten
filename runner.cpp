#include <iostream>
#include "runner.hpp"

void Runner::update() {
}

void Runner::handleInput(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Up) {
		// Jump
		std::cerr << "up" << std::endl;
	}
	else if (key == sf::Keyboard::Down) {
		// move down a level
		std::cerr << "down" << std::endl;
	}
}

