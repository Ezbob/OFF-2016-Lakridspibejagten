#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "game_state.hpp"
#include "paths.hpp"
#include <string>

class GameStateDescription : public GameState, public sf::Texture {


	public:
	sf::Font font;	
	sf::Text text;

	GameStateDescription(Game *g, std::string text) {
		game = g;
    	this->font.loadFromFile(path::font_description);
		this->text.setString(text);
	   	this->text.setCharacterSize(30);
    	this->text.setStyle(sf::Text::Bold);
    	this->text.setColor(sf::Color::Black);
    	this->text.setPosition(50, 200);
    	this->text.setFont(font);

	}

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void loadgame();
};
