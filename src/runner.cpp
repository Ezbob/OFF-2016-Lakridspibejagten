#include <iostream>
#include <string>
#include <cmath>
#include "runner.hpp"

void printVector(sf::Vector2f vec, std::string name) {
	std::cerr << name << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}

void Runner::update(const float dt) {
	int elapsed = jClock.getElapsedTime().asMilliseconds(); // since pressing UP

	if (is_jumping) {
		// Keep falling
		velocity.y += GRAVITY*dt;

		// If we hit the ground => stop falling 
		if (bottom() > ground) {
			velocity.y = 0;
			is_jumping = false;
			setY(ground - height/2);
		}
	} else {
		if (elapsed > 200 && charge_jump) { // trigger jump
			do_jump = true;
		}
	}

	// Jump
	if (do_jump) {
		int jForce = std::min(elapsed, 200);
		std::cerr << "jump force: " << jForce << std::endl;
		velocity.y = -10 - jForce/50;

		is_jumping = true;
		do_jump = false;
		charge_jump = false;
	}

	velocity.x += speed;

	shape.move({0, velocity.y});

	// Update world coordinates
	wx += velocity.x * dt;
}

void Runner::handleInputPressed(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Up) {
		std::cerr << "[KEY:up]" << std::endl;
		if (bottom() == ground && !is_jumping) {
			jClock.restart();
			charge_jump = true;
		}
	}
	else if (key == sf::Keyboard::Down) {
		std::cerr << "[KEY:down]" << std::endl;
	}
	else if (key == sf::Keyboard::D) {
		debug();
	}
}
void Runner::handleInputReleased(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Up && !is_jumping) {
		do_jump = true;
		charge_jump = false;
	}
}

void Runner::debug() {
	sf::Time elapsed = clock.getElapsedTime();

	std::cerr << "------------------" << std::endl;

	printVector(shape.getPosition(), "Position");
	printVector(velocity, "Velocity");
	std::cerr << "worldpos: " << wx << " (hor)" << std::endl;

	std::cerr << "top(" << top() << "), left(" << left() << "), ";
	std::cerr << "bottom(" << bottom() << "), right(" << right() << ")" << std::endl;

	//std::cerr << "jump: " << jump << std::endl;

	std::cerr << "Elapsed time: " << elapsed.asMilliseconds() << " ms";
	std::cerr << "\t(" << elapsed.asSeconds() << " sec)" << std::endl;
}

