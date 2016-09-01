#ifndef UUID_AF6E1164_EF92_4063_B04E_BEAB64730646
#define UUID_AF6E1164_EF92_4063_B04E_BEAB64730646

#include <SFML/Graphics.hpp>
#include <vector>
#include "object.hpp"
#include "assets.hpp"

class Stone : public Object {
	public:

	sf::Vector2f velocity{-5, 0};
	sf::Sprite sprite;

	float speed{.002};
	std::vector<float> ground_levels{600, 400, 0};

	sf::Vector2f startpos;

	Stone(float x, float y) : Object ({24, 12}), startpos(x,y) {
		sprite.setTexture(assets::rock);
		setX(x);
		setY(y);
		sprite.setOrigin(width()/2, height()/2);
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
		Object::setPosition({x(), ny+height()/2});
	}
};

#endif
