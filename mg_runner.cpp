#include "mg_runner.hpp"


void MiniGameRunner::create() {
}

void MiniGameRunner::draw(const float dt) {
	game->window.setView(view);
	game->window.clear(sf::Color::White);

	game->window.draw(runner.shape);
}

void MiniGameRunner::update(const float dt) {
	runner.update();
}

void MiniGameRunner::handleInput() {
	sf::Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: {
				game->window.close();
				break;
			}

			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Escape)
					game->window.close();
				runner.handleInput(event.key.code);
			}

			default:
				break;
		}
	}
}

MiniGameRunner::MiniGameRunner(Game *game) {
	this->game = game;
}

