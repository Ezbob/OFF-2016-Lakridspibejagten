#ifndef UUID_AF6E1164_EF92_4063_B04E_BEAB64730646
#define UUID_AF6E1164_EF92_4063_B04E_BEAB64730646

#include <SFML/Graphics.hpp>
#include "object.hpp"

class Stone : public Object {
	public:

	sf::Vector2f velocity{-5, 0};
	sf::Texture tex;
	sf::Sprite sprite;

	float width{24},
		  height{24};
	float speed{.2};

	Stone(float x, float y) {
		if (!tex.loadFromFile("assets/imgs/rock1.png"))
			std::cerr << "Error loading rock texture" << std::endl;
		sprite.setTexture(tex);
		sprite.setPosition({x, y});
		sprite.setOrigin(width/2, height/2);
	}

	void update(const float dt);
	void scale(float sx, float sy);
	void setVelocity(float vx, float vy);
	
	float x()		 { return sprite.getPosition().x; }
	float y()		 { return sprite.getPosition().y; }
	float left()	 { return x() - width / 2; }
	float right()	 { return x() + width / 2; }
	float top()		 { return y() - height / 2; }
	float bottom()	 { return y() + height / 2; }
	void setX(float x) { sprite.setPosition({x, y()}); }
	void setY(float y) { sprite.setPosition({x(), y}); }
};

#endif
