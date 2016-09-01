#include <iostream>
#include <string>
#include <cmath>
#include "runner.hpp"


int clamp(int a, int min, int max) {
	return a < min ? min : a > max ? max : a;
}

void printVector(sf::Vector2f vec, std::string name) {
	std::cerr << name << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}

void Runner::draw(sf::RenderWindow &window) {
	Object::draw(window);
	window.draw(ani);
}

void Runner::scale(float sx, float sy) {
	Object::setScale({sx, sy});
	ani.setScale({sx, sy});
}

void Runner::update(const float dt) {
	int elapsed = jClock.getElapsedTime().asMilliseconds(); // since pressing UP

	if (is_jumping) {
		// Keep falling
		velocity.y += GRAVITY*dt;

		// Go to next ground level
		
		if (bottom() < ground_levels[clamp(current_ground + 1, 0, ground_levels.size() - 1)]) {
			current_ground = clamp(current_ground + 1, 0, ground_levels.size() - 1);
			ground = ground_levels[current_ground];
		}

		// If we hit the ground => stop falling 
		if (bottom() > ground) {
			velocity.y = 0;
			is_jumping = false;
			setY(ground - height()/2);
		}
	} else {
		if (elapsed > 200 && charge_jump) { // trigger jump
			do_jump = true;
		}
	}

	// Jump
	if (do_jump) {
		int jForce = std::min(elapsed, 200);
		velocity.y = -10 - jForce/50;

		is_jumping = true;
		do_jump = false;
		charge_jump = false;
	}

	float upd = std::max(0.05, .5/log(velocity.x));
	ani.update(dt, upd);

	if (!stopped) {
		velocity.x += speed;
		Object::move({0, velocity.y});
		ani.move({0, velocity.y});
	}

	// Update world coordinates
	wx += velocity.x * dt;

}

void Runner::handleInputPressed(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Up) {
		// std::cerr << "[KEY:up]" << std::endl;
		if (bottom() == ground && !is_jumping) {
			jClock.restart();
			charge_jump = true;
		}
	}
	else if (key == sf::Keyboard::Down) {
		// std::cerr << "[KEY:down]" << std::endl;

		if (current_ground > 0) {
			current_ground = clamp(current_ground - 1, 0, ground_levels.size() - 1);
			ground = ground_levels[current_ground];
			is_jumping = true;
		}
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

void Runner::stop() {
	stopped = true;
	velocity.x = 0;
}

void Runner::debug() {
	sf::Time elapsed = clock.getElapsedTime();

	std::cerr << "------------------" << std::endl;

	printVector(ani.getPosition(), "Position");
	printVector(velocity, "Velocity");
	std::cerr << "worldpos: " << wx << " (hor)" << std::endl;

	std::cerr << "top(" << top() << "), left(" << left() << "), ";
	std::cerr << "bottom(" << bottom() << "), right(" << right() << ")" << std::endl;

	std::cerr << "ground: " << ground << ", level: " << current_ground << std::endl;

	std::cerr << "Elapsed time: " << elapsed.asMilliseconds() << " ms";
	std::cerr << "\t(" << elapsed.asSeconds() << " sec)" << std::endl;
}

