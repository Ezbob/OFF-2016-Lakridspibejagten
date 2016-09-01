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

	float ground{600};	// ground level (can be updated)
	std::vector<float> ground_levels{600, 400, 0};
	int current_ground;
	float width{48},
		  height{54};
	float speed{.2};
	float jump_force{0.25};
	float force{0};
	bool is_jumping = true;
	bool do_jump = false;
	bool charge_jump = false;

	float wx{0};

	int frame{0};
	sf::Texture tex;
	animation ani;

	Runner(float x=400, float y=100) : 
		ani({0,1,2,3,4,5}, assets::runner) {
		ani.setPosition({x - width / 2, y + height / 2});
	}

	void scale(float sx, float sy);
	void update(const float dt);
	void handleInputPressed(sf::Keyboard::Key key);
	void handleInputReleased(sf::Keyboard::Key key);
	void debug();

	float x()		 { return ani.getPosition().x; }
	float y()		 { return ani.getPosition().y; }
	float left()	 { return x() - width / 4; }
	float right()	 { return x() + width / 4; }
	float top()		 { return y() - height / 2; }
	float bottom()	 { return y() + height / 2; }
	void setX(float x) { ani.setPosition({x, y()}); }
	void setY(float y) { ani.setPosition({x(), y}); }
};

#endif
