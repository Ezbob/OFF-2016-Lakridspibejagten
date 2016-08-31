#include <SFML/Graphics.hpp>
#include <vector>

#include "game_state.hpp"
#include "gs_treeout.hpp"
#include <cmath>

template<class T1, class T2>
bool isIntersecting(T1 &mA, T2 &mB)
{
	return mA.right() >= mB.left() &&
           mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() &&
           mA.top() <= mB.bottom();
}

void testCollision(Player &mPlayer, Ball &mBall)
{
    if (!isIntersecting(mPlayer, mBall)) return;
    mBall.velocity.y = -ballVelocity;

    if (mBall.x() < mPlayer.x()) mBall.velocity.x = -ballVelocity;
    else mBall.velocity.x = ballVelocity;
}

bool testCollision(Player &mPlayer, Resource &mResource)
{
    return isIntersecting(mPlayer, mResource);
}

void testCollision(Resource &mResource, Ball &mBall)
{
    if (!isIntersecting(mResource, mBall)) return;
    mResource.hit = true;
    float overlapLeft = mBall.right() - mResource.left();
    float overlapRight = mResource.right() - mBall.left();
    float overlapTop = mBall.bottom() - mResource.top();
    float overlapBottom = mResource.bottom() - mBall.top();

    bool ballFromLeft = fabs(overlapLeft) < fabs(overlapRight);
    bool ballFromTop = fabs(overlapTop) < fabs(overlapBottom);

    float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
    float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

    if (fabs(minOverlapX) < fabs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
    else
        mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}

void GameStateTreeout::draw(const float dt) {
	this->game->window.clear(sf::Color::White);
	this->game->window.draw(this->player->shape);
	this->game->window.draw(this->ball->shape);
	for (Resource r : resources) {
		this->game->window.draw(r.shape);
	}

}

void GameStateTreeout::win() {

}

void GameStateTreeout::update(const float dt) {
	testCollision(*player, *ball);
	player->update();
	ball->update();
	for (int i = resources.size() - 1; i >= 0; i--) {
		if (resources[i].hit) {
			resources[i].update();
			if (testCollision(*player, resources[i])) {
				resources.erase(resources.begin() + i);
				localHighscore += pointsPerResource;
			}

		}
		else 
			testCollision(resources[i], *ball);
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


void GameStateTreeout::loadgame() {

	game->pushState(this);
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
}