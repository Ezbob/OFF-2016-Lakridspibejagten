#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "game_state.hpp"


void Game::pushState(GameState* state) {
	this->states.push(state);
}

void Game::popState() {
	this->states.pop();
}

void Game::changeState(GameState* state) {
	if (!this->states.empty())
		popState();
	pushState(state);
}

GameState* Game::peekState() {
	if (this->states.empty())
		return nullptr;
	return this->states.top();
}

void Game::gameloop() {
	sf::Clock clock;

	while (this->window.isOpen()) {
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();
		
		if (peekState() == nullptr)
			continue;
		peekState()->handleInput();
		peekState()->update(dt);
		
		this->window.clear(sf::Color::Black);

		peekState()->draw(dt);

		this->window.display();
	}
}

Game::Game() {
	this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jagten på lakridspiberne");
	this->window.setFramerateLimit(60);
}

Game::~Game() {
	while (!this->states.empty())
		popState();
}
