#include "gs_description.hpp"

void GameStateDescription::draw(const float dt) {
	this->game->window.clear(sf::Color::White);
	this->game->window.draw(this->text);
}

void GameStateDescription::update(const float dt) {

}

void GameStateDescription::handleInput() {
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				game->window.close();
				break;
			case sf::Event::KeyPressed:
				this->game->popState();
			default:
				break;
		}
	}
}

void GameStateDescription::loadgame() {
	return;
}