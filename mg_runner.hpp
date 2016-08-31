#ifndef MiniGameRunner_HPP
#define MiniGameRunner_HPP

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "runner.hpp"

class MiniGameRunner : public GameState {
	private:
	
	sf::View view;
	sf::Texture tex_back;
	sf::Sprite back;
	Runner runner;

	public:

	MiniGameRunner(Game *game);
	virtual void create();
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

};

#endif
