#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "game_state.hpp"
#include "assets.hpp"
#include "animation.hpp"

constexpr float ballVelocity = 8.f;
constexpr int windowWidth = 800, windowHeight = 600;
constexpr float paddleWidth = 24.f, paddleHeight = 20.f, paddleVelocity = 15.f;
constexpr float pipeWidth = 48.f, pipeHeight = 20.f;


class Player {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	animation ani;
	sf::RectangleShape shape;
	bool pIsMovingRight;
	bool pIsMovingLeft;
	bool isFacingRight = true;
	sf::Vector2f velocity;

	Player(float x, float y):ani({0,1,2,3,4,5}, assets::catcher) {
		ani.setPosition(x - 48, y - 108);
		ani.setTexture(assets::catcher);
		ani.setupFrames(assets::catcher);
		pIsMovingLeft = false;
		pIsMovingRight = false;
		shape.setPosition(x, y - 80);
		sf::Vector2f v{paddleWidth, paddleHeight};
		shape.setSize(v);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(10.f, 10.f);
		ani.setScale({2, 2});
	}

	void update(const float dt);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	float x() { return shape.getPosition().x; }
 	float y() { return shape.getPosition().y; }
 	float left() { return x() - shape.getSize().x / 2.f; }
 	float right() { return x() + shape.getSize().x / 2.f; }
 	float top() { return y() - shape.getSize().y / 2.f; }
 	float bottom() { return y() + shape.getSize().y / 2.f; }
};

class Ball {
public:
	sf::CircleShape shape;
	sf::Vector2f velocity{-ballVelocity, -ballVelocity};

	Ball(float x, float y) {
		shape.setPosition(x, y);
		shape.setRadius(10.f);
		shape.setFillColor(sf::Color::Red);
	}

	bool update();
	void reset(float x, float y);
	float x() { return shape.getPosition().x; }
 	float y() { return shape.getPosition().y; }
 	float left() { return x() - shape.getRadius(); }
 	float right() { return x() + shape.getRadius(); }
 	float top() { return y() - shape.getRadius(); }
 	float bottom() { return y() + shape.getRadius(); }
};

class Resource {
public:
	bool hit;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape shape;

	Resource(float x, float y) {
		shape.setPosition(x+12,y+18);
		sprite.setTexture(assets::pibe);
		hit = false;
		sprite.setPosition(x, y);
		sf::Vector2f v{pipeWidth, pipeHeight};
		shape.setSize(v);
		shape.setFillColor(sf::Color::Cyan);
		shape.setOrigin(10.f, 10.f);
	}

	void update();
	float x() { return shape.getPosition().x; }
 	float y() { return shape.getPosition().y; }
 	float left() { return x() - shape.getSize().x / 2.f; }
 	float right() { return x() + shape.getSize().x / 2.f; }
 	float top() { return y() - shape.getSize().y / 2.f; }
 	float bottom() { return y() + shape.getSize().y / 2.f; }
};

class Gift : Resource {
public:

	bool active = false;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape shape;

	Gift(float x, float y):Resource(x,y) {
		shape.setPosition(x, y);
		sprite.setTexture(assets::gave);
		sprite.setTextureRect(sf::IntRect(30, 0, 60, 30));
		hit = true;
		sprite.setPosition(x, y);
		sf::Vector2f v{pipeWidth/2, pipeHeight};
		shape.setSize(v);
		shape.setFillColor(sf::Color::Cyan);
		shape.setOrigin(10.f, 10.f);
	}

	void update();
	float x() { return shape.getPosition().x; }
 	float y() { return shape.getPosition().y; }
 	float left() { return x() - shape.getSize().x / 2.f; }
 	float right() { return x() + shape.getSize().x / 2.f; }
 	float top() { return y() - shape.getSize().y / 2.f; }
 	float bottom() { return y() + shape.getSize().y / 2.f; }
};

class GameStateTreeout : public GameState, public sf::Texture {

public:

	sf::Sprite background;
	Ball *ball = new Ball(300,400);
	Player *player = new Player(385, 580);
	Gift *gift = new Gift(385,200);
	std::vector<Resource> resources;
	int localHighscore = 0;
	int pointsPerResource = 1;
	int lives = 5;

	GameStateTreeout(Game *g) {
		game = g;
		background = assets::background_sprite_treeout;
		for (int i = 0; i < 4; i++)
			resources.push_back(Resource(rand() % 550 + 150, 88));
		for (int i = 0; i < 4; i++)
			resources.push_back(Resource(rand() % 550 + 150, 137));
		for (int i = 0; i < 4; i++)
			resources.push_back(Resource(rand() % 550 + 150, 184));
		for (int i = 0; i < 4; i++)
			resources.push_back(Resource(rand() % 550 + 150, 232));
		for (int i = 0; i < 4; i++)
			resources.push_back(Resource(rand() % 550 + 150, 280));
		for (int i = 0; i < 4; i++)
			resources.push_back(Resource(rand() % 550 + 150, 329));
	}

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void reset();
	void loadgame();
	void checkCollision();
	void end();
};
