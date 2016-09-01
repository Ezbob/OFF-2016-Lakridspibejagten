#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "game_state.hpp"
#include "assets.hpp"

class GameStateDescription : public GameState {
protected:
	sf::Text textLeft;
	sf::Sprite back;

public:
	GameStateDescription(Game *g, std::string t) {
		game = g;

		textLeft.setString(L"Du skal til fest!\nBørnene mangler lakridspiber,\nog der er en der fortjener en gave!\n\nEn lange rejse venter dig. Afsted!\n\n[Tryk <Space> for at starte.]");
		textLeft.setPosition({10, 400});
		textLeft.setFont(assets::font_main);
		textLeft.setCharacterSize(20);

		back.setTexture(assets::story_start);
		back.setScale({2.f, 2.f});
	}

	void draw(const float dt);
	void update(const float dt);
	void handleInput();
};
