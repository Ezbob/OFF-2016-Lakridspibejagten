#include "game.hpp"
#include "game_state.hpp"

void Game::gameloop() {
	sf::Clock clock;

	while (this->window.isOpen()) {
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();
		
		// handle input
		// update
		this->window.clear(sf::Color::Black);
		// draw
		this->window.display();
	}
}

Game::Game() {
	this->window.create(sf::VideoMode(800, 600), "OFF the Jam");
	this->window.setFramerateLimit(60);
}

Game::~Game() {
	// clean up
}	
