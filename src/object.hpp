#ifndef UUID_541333DC_4350_4653_9232_90BF754D6ACD
#define UUID_541333DC_4350_4653_9232_90BF754D6ACD

#include <SFML/Graphics.hpp>

class Object : public sf::RectangleShape {
	public:

	Object(const sf::Vector2f &size=sf::Vector2f(0,0)) : RectangleShape(size) {
		setFillColor(sf::Color::Transparent);
		setOutlineColor(sf::Color::Red);
		setOutlineThickness(2);
		setOrigin(width()/2, height()/2);
	}

	float x()		{ return getPosition().x; }
	float y()		{ return getPosition().y; }
	float left()	{ return x() - getGlobalBounds().width / 2; }
	float right()	{ return x() + getGlobalBounds().width / 2; }
	float top()		{ return y() - getGlobalBounds().height / 2; }
	float bottom()	{ return y() + getGlobalBounds().height / 2; }

	float width()	{ return getGlobalBounds().width; }
	float height()	{ return getGlobalBounds().height; }

	virtual void draw(sf::RenderWindow &window);
};

#endif
