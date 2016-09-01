#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "game_state.hpp"
#include "assets.hpp"


void Game::pushState(GameState* state) {
	this->states.push(state);
	state->reset();
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

	while (this->window.isOpen() && states.empty() == false) {
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr)
			continue;
		peekState()->handleInput();
		peekState()->update(dt);
		
		this->window.clear(sf::Color::Black);

		peekState()->draw(dt);
		drawHighscore(this->window);

		this->window.display();
	}
}

void Game::drawHighscore(sf::RenderWindow &window) {
	window.draw(icon_pibe);
	text_pibe.setString(std::to_string(score_pibe));
	window.draw(text_pibe);

	window.draw(icon_gave);
}

Game::Game() {
	this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lakridspibejagten");
	this->window.setFramerateLimit(60);

	icon_gave.setTexture(assets::gave);
	icon_gave.setPosition({10,50});
	auto r = icon_gave.getTextureRect();
	r.width = 30;
	icon_gave.setTextureRect(r);

	icon_pibe.setPosition({10,10});
	icon_pibe.setTexture(assets::pibe);
	// Setup highscore
	text_pibe.setFont(assets::font_main);
	text_pibe.setCharacterSize(30);
	text_pibe.setStyle(sf::Text::Bold);
	text_pibe.setColor(sf::Color::Black);
	text_pibe.setPosition(65, 10);
}

Game::~Game() {
	while (!this->states.empty())
		popState();
}
