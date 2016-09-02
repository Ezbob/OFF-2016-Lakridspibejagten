#ifndef UUID_E996F088_F036_4606_906C_8A689CD9A27D
#define UUID_E996F088_F036_4606_906C_8A689CD9A27D

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "animation.hpp"
#include "assets.hpp"

constexpr float GRAVITY{25};

class Runner : public Object {
	public:
	sf::Vector2f velocity{50, 0}; 
	sf::Clock clock, jClock;

	float ground{400};	// ground level (can be updated)
	std::vector<float> ground_levels{580, 400, 0};
	int current_ground{1};
	float speed{.2};
	float jump_force{0.25};
	float force{0};
	bool is_jumping = true;
	bool do_jump = false;
	bool charge_jump = false;
	bool stopped{false};
	int choice{0};

	float wx{0};

	sf::Texture tex;
	animation ani;

	Runner(float x=200, float y=100) : Object({48-30,56-5}), ani({0,1,2,3,4,5},assets::runner,48) {
		setX(x);
		setY(y);
		ani.setOrigin(width()/2, height()/2);
		setOrigin(-width()/4+5, height()/2);
	}

	void scale(float sx, float sy);
	void update(const float dt);
	void handleInputPressed(sf::Keyboard::Key key);
	void handleInputReleased(sf::Keyboard::Key key);
	void debug();
	void draw(sf::RenderWindow &window);
	void stop();

	void setX(float nx) {
		Object::setPosition({nx, y()});
		ani.setPosition({nx, y()});
	}
	void setY(float ny) {
		Object::setPosition({x(), ny});
		ani.setPosition({x(), ny});
	}
};

#endif
