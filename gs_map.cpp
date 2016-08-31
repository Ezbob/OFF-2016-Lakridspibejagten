#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "gs_map.hpp"

void GameStateMap::draw(const float dt) {
	this->game->window.setView(this->view);
	this->game->window.clear(sf::Color::Black);
	// this->game->window.draw( /*background here*/ );
}

void GameStateMap::update(const float dt) {
}

void GameStateMap::handleInput() {
	sf::Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: {
				game->window.close();
				break;
			}

			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Escape)
					this->game->window.close();
			}

			default:
				break;
		}
	}
}

void GameStateMap::loadgame() {
	this->game->pushState(new GameStateMap(this->game));
}	

GameStateMap::GameStateMap(Game *game) {
	this->game = game;
}
