#ifndef UUID_AF6E1164_EF92_4063_B04E_BEAB64730646
#define UUID_AF6E1164_EF92_4063_B04E_BEAB64730646

#include <SFML/Graphics.hpp>
#include "object.hpp"

class Stone : public Object {
	public:

	sf::Vector2f velocity{-5, 0};
	sf::Texture tex;
	sf::Sprite sprite;

	float speed{.2};

	Stone(float x, float y) : Object ({24, 12}) {
		if (!tex.loadFromFile("assets/imgs/rock1.png"))
			std::cerr << "Error loading rock texture" << std::endl;
		sprite.setTexture(tex);
		setX(x);
		setY(y);
		sprite.setOrigin(width()/2, height()/2);
		scale(2.f, 2.f);
	}

	void update(const float dt);
	void reset();
	void scale(float sx, float sy);
	void setVelocity(float vx, float vy);
	void draw(sf::RenderWindow &window);
	
	void setX(float nx) {
		sprite.setPosition({nx, y()});
		Object::setPosition({nx, y()});
	}
	void setY(float ny) {
		sprite.setPosition({x(), ny});
		Object::setPosition({x(), ny});
	}
};

#endif
