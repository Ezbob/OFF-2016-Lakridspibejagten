#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "game_state.hpp"

constexpr float ballVelocity = 8.f;
constexpr int windowWidth = 800, windowHeight = 600;
constexpr float paddleWidth = 60.f, paddleHeight = 20.f, paddleVelocity = 9.f;

class Player {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	bool pIsMovingRight;
	bool pIsMovingLeft;
	sf::Vector2f velocity;

	Player(float x, float y, char *texture) {
		shape.setPosition(x,y);
		if (!this->texture.loadFromFile(texture)) printf("Texture missing\n");
		sprite.setTexture(this->texture);
		pIsMovingLeft = false;
		pIsMovingRight = false;
		shape.setPosition(x, y);
		sf::Vector2f v{paddleWidth, paddleHeight};
		shape.setSize(v);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(10.f, 10.f);
	}

	void update();
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
		shape.setOrigin(10.f, 10.f);
	}
	bool update();
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
	sf::CircleShape shape;

	Resource(float x, float y, char *texture) {
		shape.setPosition(x,y);
		if (!this->texture.loadFromFile(texture)) printf("Texture missing\n");
		this->sprite.setTexture(this->texture);
		this->hit = false;
		shape.setRadius(10.f);
		shape.setFillColor(sf::Color::Cyan);
		shape.setOrigin(10.f, 10.f);
	}

	void update();
 	float x() { return shape.getPosition().x; }
 	float y() { return shape.getPosition().y; }
 	float left() { return x() - shape.getRadius(); }
 	float right() { return x() + shape.getRadius(); }
 	float top() { return y() - shape.getRadius(); }
 	float bottom() { return y() + shape.getRadius(); }
};

class GameStateTreeout : public GameState, public sf::Texture {

public:

	Ball *ball = new Ball(0,0);
	Player *player = new Player(385, 580, "");
	std::vector<Resource> resources;
	int localHighscore = 0;
	int pointsPerResource = 50;
	int paddleHitsRemaining = 10;

	GameStateTreeout(Game *g) {
		game = g;
		for (int i = 0; i < 50; i++) {
            resources.push_back(Resource(rand() % 600 + 100, rand() % 400 + 100, ""));
        }
	}

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void init();
	void loadgame();
	void checkCollision();
	void end();
};