#include "mg_runner.hpp"
#include "stone.hpp"

void MiniGameRunner::create() {
}

void MiniGameRunner::draw(const float dt) {
	game->window.setView(view);
	game->window.clear(sf::Color::White);

	game->window.draw(back);
	game->window.draw(runner.shape);
	game->window.draw(stone.shape);
}

void MiniGameRunner::update(const float dt) {
	runner.update(dt);
	//stone.update(dt);
	// Update background
	//back.setTextureRect(IntRect(..., ...., ...., ....));
	//back.move({-runner.velocity.x, 0});
	//
	back.setTextureRect(sf::IntRect(runner.wx, 0, 800, 600));
}

void MiniGameRunner::handleInput() {
	sf::Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				game->window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					game->window.close();
				runner.handleInputPressed(event.key.code);
				break;

			case sf::Event::KeyReleased:
				runner.handleInputReleased(event.key.code);
				break;

			default:
				break;
		}
	}
}

MiniGameRunner::MiniGameRunner(Game *game) : stone(500, 585) {
	this->game = game;

	// Load background
	if (tex_back.loadFromFile("assets/tiling_background.png")) {
		tex_back.setRepeated(true);
		tex_back.setSmooth(true);
		back.setTexture(tex_back, true);
	} else {
		std::cerr << "An error occoured loading an asset." << std::endl;
	}
}

