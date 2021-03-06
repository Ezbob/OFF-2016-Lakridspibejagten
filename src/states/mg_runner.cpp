#include "mg_runner.hpp"
#include "stone.hpp"
#include "assets.hpp"

void MiniGameRunner::draw(const float dt) {
	do_nothing(dt);

	game->window.clear(sf::Color::White);

	// Draw backgrounds
	game->window.draw(back_sky);
	game->window.draw(back_mountains);
	game->window.draw(back_trees);
	game->window.draw(back_grass);
	// runner, stones, pibe
	runner.draw(game->window);
	for (auto& stone : stones) {
		stone.draw(game->window);
	}
	pibe.draw(game->window);
	gave.draw(game->window);
}

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB) {
	return (mA.right() >= mB.left()) && (mA.left() <= mB.right())
		&& (mA.bottom() >= mB.top()) && (mA.top() <= mB.bottom());
}

void MiniGameRunner::update(const float dt) {
	runner.update(dt);
	for (auto& stone : stones) {
		stone.update(dt);
		if (isIntersecting(stone, runner)) {
			// skift state... læg en beskrivelse ind istedet
			game->popState();
		}
	}
	
	pibe.update(dt);
	gave.update(dt);

	if (isIntersecting(pibe, runner)) {
		pibe.reset();
		game->score_pibe++;
	}

	if (isIntersecting(gave, runner)) {
		gave.reset();
		game->score_gave = true;
	}
	// Update backgrounds
	back_pos_sky += 25 * dt / 10;
	back_sky.setTextureRect(sf::IntRect(back_pos_sky, 0, 400, 300));
	back_pos_mountains += 15 * dt / 5;
	back_mountains.setTextureRect(sf::IntRect(back_pos_mountains, 0, 400, 300));
	back_pos_trees += runner.velocity.x * dt;
	back_trees.setTextureRect(sf::IntRect(back_pos_trees, 0, 400, 300));
	back_pos_grass += runner.velocity.x * dt;
	back_grass.setTextureRect(sf::IntRect(back_pos_grass, 0, 400, 300));

	// Finished?
	if (runner.wx > goalline && !gave.active && !game->score_gave) {
		std::cerr << "gave?" << std::endl;
		gave.reset();
		gave.setY(250);
	}

}

void MiniGameRunner::handleInput() {
	sf::Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				game->window.close();
				break;

			case sf::Event::Resized:
				//view.setSize(event.size.width, event.size.height);
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					game->popState();
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

MiniGameRunner::MiniGameRunner(Game *game) {
	this->game = game;

	back_sky.setTexture(assets::back_sky, true);
	back_sky.setScale({2.f,2.f});
	back_mountains.setTexture(assets::back_mountains, true);
	back_mountains.setScale({2.f,2.f});
	back_trees.setTexture(assets::back_trees, true);
	back_trees.setScale({2.f,2.f});
	back_trees.setPosition({0,-80});
	back_grass.setTexture(assets::back_grass, true);
	back_grass.setScale({2.f,2.f});

	for (int i=0; i<num_stones; i++)
		stones.emplace_back(800 + 400*i, 600);

	runner.scale(2.f, 2.f);
	for (auto& stone : stones) {
		stone.reset();
	}

	gave.sprite.setScale({2.f,2.f});
	gave.setScale({2.f,2.f});
	gave.setX(-100);
	gave.setY(300);
	gave.setInactive();

	//pibe.reset();
}


void MiniGameRunner::reset() {
}
