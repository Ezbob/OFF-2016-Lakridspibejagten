#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "gs_treeout.hpp"

void GameStateTreeout::draw(const float dt) {
	this->game->window.clear(sf::Color::White);
	this->game->window.draw(this->player->shape);
	this->game->window.draw(this->ball->shape);
	for (Resource r : this->resources) {
		this->game->window.draw(r.shape);
	}
}

void GameStateTreeout::win() {

}

void GameStateTreeout::update(const float dt) {
	player->update();
	ball->update();
	for (Resource r : resources) {
		if (r.hit)
			r.update();
	}
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::A)
		pIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		pIsMovingRight = isPressed;
}

void GameStateTreeout::handleInput() {
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				game->window.close();
				break;
			case sf::Event::KeyPressed:
				this->player->handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				this->player->handlePlayerInput(event.key.code, false);
				break;
			default:
				break;
		}
	}
}


void GameStateTreeout::loadgame() {

	game->pushState(this);
}

template<class T1, class T2>
bool isIntersecting(T1 &mA, T2 &mB)
{
	return mA.right() >= mB.left() &&
           mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() &&
           mA.top() <= mB.bottom();
}


void Ball::update() {
 	shape.move(velocity);
	if (left() < 0)
		velocity.x = ballVelocity;
	else if (right() > windowWidth)
		velocity.x = -ballVelocity;
 	if (top() < 0)
 		velocity.y = ballVelocity;
 	else if(bottom() > windowHeight)
 		velocity.y = -ballVelocity;
}

void Player::update() {
	shape.move(velocity);
	if (pIsMovingLeft
		&& left() > 0)
	{
		velocity.x = -paddleVelocity;
	}
	else if (pIsMovingRight
		&& right() < windowWidth)
	{
		velocity.x = paddleVelocity;
	}
	else
	{
		velocity.x = 0;
	}
}

void Resource::update() {

}