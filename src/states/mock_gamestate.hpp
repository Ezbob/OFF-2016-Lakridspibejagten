#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "game_state.hpp"

class GameStateMockMiniGame : public GameState, public sf::Texture {

	public:
	GameStateMockMiniGame(Game *g) {
		game = g;
	}

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void loadgame();
};