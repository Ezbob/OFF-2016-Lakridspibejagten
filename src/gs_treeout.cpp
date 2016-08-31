#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "game_state.hpp"
#include "gs_treeout.hpp"
#include <cmath>
#include "gs_description.hpp"
#include "paths.hpp"

template<class T1, class T2>
bool isIntersecting(T1 &mA, T2 &mB)
{
	std::cerr << __func__ << " " << __LINE__ << "\n";
	return mA.right() >= mB.left() &&
           mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() &&
           mA.top() <= mB.bottom();
}

bool testCollision(Player &mPlayer, Ball &mBall)
{
	std::cerr << __func__ << " " << __LINE__ << "\n";
    if (!isIntersecting(mPlayer, mBall)) return false;
    
    mBall.velocity.y = -ballVelocity;

    if (mBall.x() < mPlayer.x()) mBall.velocity.x = -ballVelocity;
    else mBall.velocity.x = ballVelocity;
    return true;
}

bool testCollision(Player &mPlayer, Resource &mResource)
{
	std::cerr << __func__ << " " << __LINE__ << "\n";
	    return isIntersecting(mPlayer, mResource);
}

void testCollision(Resource &mResource, Ball &mBall)
{
	std::cerr << __func__ << " " << __LINE__ << "\n";
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
	// Set up font
	std::cerr << __func__ << " " << __LINE__ << "\n";
    sf::Font font;
    font.loadFromFile(path::font);

	// Set up paddle text
	static sf::Text * paddleText = new sf::Text();
    std::string str = "Paddle hits left: " + std::to_string(this->paddleHitsRemaining) + "\n";
    paddleText->setString(str);
    paddleText->setCharacterSize(30);
    paddleText->setStyle(sf::Text::Bold);
    paddleText->setColor(sf::Color::Black);
    paddleText->setPosition(450, 50);
    paddleText->setFont(font);

    // Set up point text
	static sf::Text * pointText = new sf::Text();

    str = "Points scored: " + std::to_string(this->localHighscore) + "\n";
    pointText->setString(str);
    pointText->setCharacterSize(30);
    pointText->setStyle(sf::Text::Bold);
    pointText->setColor(sf::Color::Black);
    pointText->setPosition(450, 100);
    pointText->setFont(font);

    // clear
    this->game->window.clear(sf::Color::White);
	
    // draw entities
	this->game->window.draw(this->player->shape);
	this->game->window.draw(this->ball->shape);
	for (Resource r : resources)
		this->game->window.draw(r.shape);
	
	// draw HUD/texts
	this->game->window.draw(*paddleText);
	this->game->window.draw(*pointText);
}

void GameStateTreeout::end() {
	std::cerr << __func__ << " " << __LINE__ << "\n";
	this->game->currentScore += this->localHighscore;
	game->popState();
}

void GameStateTreeout::update(const float dt) {
	std::cerr << __func__ << " " << __LINE__ << "\n";
	if (paddleHitsRemaining <= 0)
		end();
	if (testCollision(*player, *ball))
		this->paddleHitsRemaining -= 1;
	player->update();
	if (ball->update()) // Hit the bottom
		this->paddleHitsRemaining -= 2;
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

void GameStateTreeout::reset() {

}

void GameStateTreeout::loadgame() {
	std::cerr << __func__ << " " << __LINE__ << "\n";
	//game->pushState(new GameStateDescription(this->game, "As the ball hits RESOURCES, catch them to earn points. \n Each time the ball hits the bottom, two paddle hits are subtracted, \n each time it hits the paddle, one is subtracted. \n When it reaches zero, the game is over.\n"));
}


bool Ball::update() {
 	std::cerr << __func__ << " " << __LINE__ << "\n";
 	shape.move(velocity);
	if (left() < 0)
		velocity.x = ballVelocity;
	else if (right() > windowWidth)
		velocity.x = -ballVelocity;
 	if (top() < 0)
 		velocity.y = ballVelocity;
 	else if(bottom() > windowHeight){
 	 	velocity.y = -ballVelocity;
 		return true;
	}
	return false;
}

void Player::update() {
	std::cerr << __func__ << " " << __LINE__ << "\n";
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
	std::cerr << __func__ << " " << __LINE__ << "\n";
	sf::Vector2f v{0.f, 5.f};
	shape.move(v);
}
