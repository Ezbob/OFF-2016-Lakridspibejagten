#ifndef UUID_E996F088_F036_4606_906C_8A689CD9A27D
#define UUID_E996F088_F036_4606_906C_8A689CD9A27D

#include <SFML/Graphics.hpp>
#include "object.hpp"

constexpr float GRAVITY{25};

class Runner : public Object {
	public:
	sf::Vector2f velocity{30, 0}; 
	sf::RectangleShape shape; // player sprite placeholder
	sf::Clock clock, jClock;

	float ground{600};	// ground level (can be updated)
	float width{50},
		  height{100};
	float speed{.03};
	float jump_force{0.25};
	float force{0};
	bool is_jumping = true;
	bool do_jump = false;
	bool charge_jump = false;

	float wx{0};

	Runner(float x=50, float y=100) {
		shape.setPosition(x, y);
		shape.setSize({width, height});
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(width/2, height/2);
	}

	void update(const float dt);
	void handleInputPressed(sf::Keyboard::Key key);
	void handleInputReleased(sf::Keyboard::Key key);
	void debug();

	float x()		 { return shape.getPosition().x; }
	float y()		 { return shape.getPosition().y; }
	float left()	 { return x() - shape.getSize().x / 2; }
	float right()	 { return x() + shape.getSize().x / 2; }
	float top()		 { return y() - shape.getSize().y / 2; }
	float bottom()	 { return y() + shape.getSize().y / 2; }
	void setX(float x) { shape.setPosition(x, y()); }
	void setY(float y) { shape.setPosition(x(), y); }
};

#endif
