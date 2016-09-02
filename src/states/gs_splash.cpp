#include "gs_splash.hpp"

void GameStateSplash::draw(const float dt) {
	do_nothing(dt);

	game->window.clear(sf::Color::White);

	time += dt;
	if (time > 0.2) {
		time = 0.0;
		frame = (frame+1) % 12;
		back_rect.left = frame * 400;
		back.setTextureRect(back_rect);
	}

	game->window.draw(back);
}

void GameStateSplash::update(const float dt) {
	do_nothing(dt);
}

void GameStateSplash::handleInput() {
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

