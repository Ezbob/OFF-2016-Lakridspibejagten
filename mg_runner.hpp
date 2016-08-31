#ifndef MiniGameRunner_HPP
#define MiniGameRunner_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "game_state.hpp"

class Runner {
	public:
	sf::Vector2f velocity{0, 0};
	sf::RectangleShape shape; // player sprite placeholder

	Runner(float x = 50, float y = 550) {
		shape.setPosition(x, y);
		shape.setSize({50, 100});
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(25, 50);
	}

	void update() {
	}
	void handleInput(sf::Keyboard::Key key) {
		if (key == sf::Keyboard::Up) {
			// Jump
			std::cerr << "up" << std::endl;
		}
		else if (key == sf::Keyboard::Down) {
			// move down a level
			std::cerr << "down" << std::endl;
		}
	}
};

class MiniGameRunner : public GameState {
	private:
	
	sf::View view;
	Runner runner;

	public:

	MiniGameRunner(Game *game);
	virtual void create();
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

};

#endif
