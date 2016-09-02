#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <unistd.h>

#include "game_state.hpp"
#include "gs_treeout.hpp"
#include "gs_description.hpp"
#include "assets.hpp"

#define localDebug 0

bool activateBall = false;

template<class T1, class T2>
bool isIntersecting(T1 &mA, T2 &mB)
{
	return mA.right() >= mB.left() &&
           mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() &&
           mA.top() <= mB.bottom();
}

bool testCollision(Player &mPlayer, Ball &mBall)
{
    if (!isIntersecting(mPlayer, mBall)) return false;
    
    mBall.velocity.y = -ballVelocity;
	float xdiff = mBall.x() - mPlayer.x();
    mBall.velocity.x = xdiff / (paddleWidth/2.f) * ballVelocity;
	return true;
}

bool testCollision(Player &mPlayer, Resource &mResource)
{
	return isIntersecting(mPlayer, mResource);
}

bool testCollision(Player &mPlayer, Gift &mGift)
{
	return isIntersecting(mPlayer, mGift);
}

void testCollision(Resource &mResource, Ball &mBall)
{
    if (!isIntersecting(mResource, mBall)) return;
    mResource.hit = true;

	float xdiff = mBall.x() - mResource.x();
    mBall.velocity.x = xdiff / (pipeWidth/2.f) * ballVelocity;
}

void GameStateTreeout::draw(const float dt) {

    // clear
    this->game->window.clear(sf::Color::White);
	this->game->window.draw(this->background);
    // draw entities
	this->game->window.draw(this->player->ani);
	if (localDebug)
		this->game->window.draw(this->player->shape);
	this->game->window.draw(this->ball->shape);
	for (Resource r : resources) {
		this->game->window.draw(r.sprite);
	}
	if (gift->active) {
		this->game->window.draw(this->gift->sprite);
		if (localDebug)
			this->game->window.draw(this->gift->shape);
	}
	
	// draw HUD/texts
	sf::CircleShape life;
	life.setRadius(12.f);
	life.setFillColor(sf::Color::Red);
	if (this->lives >= 5) {
		life.setPosition(744, 531);
		this->game->window.draw(life);
	}
	if (this->lives >= 4) {
		life.setPosition(770, 543);
		this->game->window.draw(life);
	} 
	if (this->lives >= 3) {
		life.setPosition(751, 554);
		this->game->window.draw(life);
	}
	if (this->lives >= 2) {
		life.setPosition(772, 566);
		this->game->window.draw(life);
	}
	if (this->lives >= 1) {
		life.setPosition(750, 576);
		this->game->window.draw(life);
	}
	this->game->window.draw(this->basket);
}

void GameStateTreeout::end() {
	sf::Clock clock;
	clock.restart();
	while (clock.getElapsedTime().asMilliseconds() < 500);
	game->popState();
}

void GameStateTreeout::update(const float dt) {
	if (resources.size() <= 0 && game->score_gave == false) {
		gift->active = true;
	}
	if (resources.size() <= 0 && this->gift->y() > 800)
	{
		end();
	}
	if (gift->active)
		gift->update();
	testCollision(*player, *ball);
	if (testCollision(*player, *gift)) {
		this->game->score_gave = true;
		end();
	}

	player->update(dt);

	for (int i = resources.size() - 1; i >= 0; i--) {
		if (resources[i].hit) {
			resources[i].update();
			if (testCollision(*player, resources[i])) {
				resources.erase(resources.begin() + i);
				game->score_pibe += pointsPerResource;
			}
			if (resources[i].y() > 600)
				resources.erase(resources.begin() + i);
		}
		else 
			testCollision(resources[i], *ball);
	}
	if (activateBall == false)
		ball->shape.setPosition({player->x() - 5, player->y()-40});
	else if (ball->update()) {
		lives--;
		if (lives >= 0)
			ball->reset(player->x(), player->y());
		else
			end();
	}
}

void Ball::reset(float x, float y) {
	shape.setPosition(x, y - 30);
	velocity.y = -ballVelocity;
	activateBall = false;
	sf::Clock clock;
	clock.restart();
	while (clock.getElapsedTime().asMilliseconds() < 200);
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up || key == sf::Keyboard::Space)
		activateBall = true;
	if (key == sf::Keyboard::Left)
		pIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
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
				if (event.key.code == sf::Keyboard::Escape)
					this->game->popState();
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

void GameStateTreeout::reset() {

}

void GameStateTreeout::loadgame() {

}


bool Ball::update() {
  	shape.move(velocity);
	if (left() < 0)
		velocity.x = fabs(velocity.x);
	else if (right() > windowWidth)
		velocity.x = -fabs(velocity.x);
 	if (top() < 0)
 		velocity.y = ballVelocity;
 	else if(bottom() > windowHeight){
 		return true;
	}
	return false;
}

void Player::update(const float dt) {
	ani.move(velocity);
	shape.move(velocity);
	float upd = std::max(0.05, .5/(velocity.x));
	ani.update(dt, upd);
	if (pIsMovingLeft
		&& left() > 0 + paddleWidth/2)
	{
		velocity.x = -paddleVelocity;
	}
	else if (pIsMovingRight
		&& right() < windowWidth - paddleWidth/2)
	{
		velocity.x = paddleVelocity;
	}
	else
	{
		velocity.x = 0;
	} 
}


void Resource::update() {
	sf::Vector2f v{0.f, 5.f};
	shape.move(v);
	sprite.move(v);
}

void Gift::update() {
	sf::Vector2f v{0.f, 5.f};
	shape.move(v);
	sprite.move(v);
}
