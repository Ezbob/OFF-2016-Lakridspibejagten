#ifndef UUID_AF6E1164_EF92_4063_B04E_BEAB64730646
#define UUID_AF6E1164_EF92_4063_B04E_BEAB64730646

#include <SFML/Graphics.hpp>
#include "object.hpp"

class Stone : public Object {
	public:

	sf::CircleShape shape;
	sf::Vector2f velocity{-5, 0};

	Stone(float x, float y) {
		shape.setPosition(x, y);
		shape.setRadius(15);
		shape.setFillColor(sf::Color::Blue);
		shape.setOrigin(15, 15);
	}

	void update(const float dt);
	void setVelocity(float vx, float vy);
	
	float x()		 { return shape.getPosition().x; }
	float y()		 { return shape.getPosition().y; }
	float left()	 { return x() - shape.getRadius(); }
	float right()	 { return x() + shape.getRadius(); }
	float top()		 { return y() - shape.getRadius(); }
	float bottom()	 { return y() + shape.getRadius(); }
	void setX(float x) { shape.setPosition(x, y()); }
	void setY(float y) { shape.setPosition(x(), y); }
};

#endif
