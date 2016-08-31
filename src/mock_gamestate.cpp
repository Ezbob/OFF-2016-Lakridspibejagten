#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "mock_gamestate.hpp"

void GameStateMockMiniGame::draw(const float dt) {
	sf::Text * text = new sf::Text();
	sf::Font font;
	//font.loadFromFile("AmazDooMLeft.ttf");
	font.loadFromFile("DejaVuSansCondensed.ttf");
    text->setString("You have started a minigame\nPress any key to continue.");
    text->setCharacterSize(30);
    text->setStyle(sf::Text::Bold);
    text->setColor(sf::Color::Black);
    text->setPosition(200,200);
    text->setFont(font);
    this->game->window.clear(sf::Color::White);
	this->game->window.draw(*text);
	delete text;
}

void GameStateMockMiniGame::update(const float dt) {

}

void GameStateMockMiniGame::handleInput() {
	sf::Event event;
	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				game->window.close();
				break;
			case sf::Event::KeyPressed:
				game->popState();
				break;
			default:
				break;
		}
	}
}

void GameStateMockMiniGame::loadgame() {
	game->pushState(this);
}
