#ifndef UUID_E996F088_F036_4606_906C_8A689CD9A27D
#define UUID_E996F088_F036_4606_906C_8A689CD9A27D

#include <SFML/Graphics.hpp>
#include "object.hpp"

class Runner : public object {
	public:
	sf::Vector2f velocity{0, 0};
	sf::RectangleShape shape; // player sprite placeholder

	Runner(float x = 50, float y = 550) {
		shape.setPosition(x, y);
		shape.setSize({50, 100});
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(25, 50);
	}

	void update();
	void handleInput(sf::Keyboard::Key key);

	float x()		 { return shape.getPosition().x; }
	float y()		 { return shape.getPosition().y; }
	float left()	 { return x() - shape.getSize().x / 2; }
	float right()	 { return x() + shape.getSize().x / 2; }
	float top()		 { return y() - shape.getSize().y / 2; }
	float bottom()	 { return y() + shape.getSize().y / 2; }
};

#endif
