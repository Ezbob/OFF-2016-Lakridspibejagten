#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "game_state.hpp"
#include "assets.hpp"

class GameStateDescription : public GameState, public sf::Texture {


	public:
	sf::Font font;	
	sf::Text text;

	GameStateDescription(Game *g, std::string text) {
		game = g;

		this->text.setString(text);
	   	this->text.setCharacterSize(30);
    	this->text.setStyle(sf::Text::Bold);
    	this->text.setColor(sf::Color::Black);
    	this->text.setPosition(50, 200);
    	this->text.setFont(assets::font_main);

	}

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void loadgame();
};
