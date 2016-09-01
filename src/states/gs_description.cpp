#include "gs_description.hpp"

void GameStateDescription::draw(const float dt) {
	game->window.clear(sf::Color::White);
	game->window.draw(back);
	game->window.draw(textLeft);
}

void GameStateDescription::update(const float dt) {
	return;
}

void GameStateDescription::handleInput() {
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				game->window.close();
				break;
			case sf::Event::KeyPressed:
				game->popState();
			default:
				break;
		}
	}
}

