#ifndef UUID_AF6E1164_EF92_4063_B04E_BEAB64730646
#define UUID_AF6E1164_EF92_4063_B04E_BEAB64730646

#include <SFML/Graphics.hpp>
#include <vector>
#include "object.hpp"
#include "assets.hpp"

class Stone : public Object {
	public:

	sf::Vector2f velocity{-2, 0};
	sf::Sprite sprite;

	float speed{.007};
	std::vector<float> ground_levels{580, 400, 0};

	sf::Vector2f startpos;

	Stone(float x, float y) : Object ({16, 12}), startpos(x,y) {
		sprite.setTexture(assets::rock);
		setX(x);
		setY(y);
		sprite.setOrigin(3*width()/4, height()/2+3);
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
