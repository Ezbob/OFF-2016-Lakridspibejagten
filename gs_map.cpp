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


void GameStateMap::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Escape) {
		this->game->window.close();
		return;
	}
	if (key == sf::Keyboard::W)
		// playerIsMovingUp = isPressed;
		printf("Moving up.\n");
	else if (key == sf::Keyboard::S)
		//playerIsMovingDown = isPressed;
		printf("Moving down.\n");
	else if (key == sf::Keyboard::A)
		//playerIsMovingLeft = isPressed;
		printf("Moving left.\n");
	else if (key == sf::Keyboard::D)
		//playerIsMovingRight = isPressed;
		printf("Moving right.\n");
}

void GameStateMap::handleInput() {
	sf::Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				game->window.close();
				break;
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			default:
				break;
		}
	}
}

void GameStateMap::loadgame() {
	game->pushState(this);
}