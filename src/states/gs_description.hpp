#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "game_state.hpp"
#include "assets.hpp"

class GameStateDescription : public GameState {
protected:
	sf::Text text;

public:
	GameStateDescription(Game *g, std::string t) {
		game = g;
		text.setString(t);
		text.setFont(assets::font_main);
	}

	void draw(const float dt);
	void update(const float dt);
	void handleInput();
	void loadgame();
};
