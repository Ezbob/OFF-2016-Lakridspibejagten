#include "mg_runner.hpp"
#include "stone.hpp"
#include "assets.hpp"

void MiniGameRunner::draw(const float dt) {
	game->window.clear(sf::Color::White);

	// Draw background, runner, stones, pibe
	game->window.draw(back);
	runner.draw(game->window);
	for (auto& stone : stones) {
		stone.draw(game->window);
	}
	pibe.draw(game->window);
	gave.draw(game->window);
}

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB) {
	return mA.right() >= mB.left() && mA.left() <= mB.right()
		&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void MiniGameRunner::testCollision(Stone& stone, Runner& runner) {
	if (!isIntersecting(stone, runner) && !got_gift)
		return;

	// Collision
	game->popState();
}

void MiniGameRunner::testCollision(Pibe& pibe, Runner& runner) {
	if (!isIntersecting(pibe, runner)) 
		return;

	// Collision
	game->score_pibe++;
	pibe.reset();
}

void MiniGameRunner::testCollision(Gave& gave, Runner& runner) {
	if (!isIntersecting(gave, runner)) 
		return;

	// Collision
	game->score_gave = true;
	gave.setX(-100);
	auto r = game->icon_gave.getTextureRect();
	r.left += 30;
	game->icon_gave.setTextureRect(r);
	gave.setInactive();
	got_gift = true;
	clock1.restart();
	runner.stop();
}

void MiniGameRunner::update(const float dt) {
	runner.update(dt);
	for (auto& stone : stones) {
		stone.update(dt);
		testCollision(stone, runner);
	}
	pibe.update(dt);
	gave.update(dt);
	testCollision(pibe, runner);
	testCollision(gave, runner);
	// Update background
	back_pos += runner.velocity.x * dt;
	back.setTextureRect(sf::IntRect(back_pos, 0, 800, 600));
	// Finished?
	if (runner.wx > goalline && !gave.active && !game->score_gave) {
		std::cerr << "gave?" << std::endl;
		gave.reset();
	}
	// Quit
	if (got_gift) {
		std::cerr << "[elapsed:" << clock1.getElapsedTime().asMilliseconds() << "]" << std::endl;
		if (clock1.getElapsedTime().asMilliseconds() > 2000) {
			std::cerr << "[finito -> pop]" << std::endl;
			game->popState();
		}
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
					game->window.close();
				else if (event.key.code == sf::Keyboard::S)
					game->window.setFramerateLimit(5);
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

	back.setTexture(assets::background, true);

	for (int i=0; i<num_stones; i++)
		stones.emplace_back(800 + 400*i, 600);

	runner.scale(2.f, 2.f);
	for (auto& stone : stones) {
		stone.reset();
	}

	gave.setX(-100);
	gave.setInactive();

	//pibe.reset();
}


void MiniGameRunner::reset() {
}
