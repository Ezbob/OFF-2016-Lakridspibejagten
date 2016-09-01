#ifndef UUID_EF098647_2504_40B0_9E44_A8F183DD17B2
#define UUID_EF098647_2504_40B0_9E44_A8F183DD17B2

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "assets.hpp"

class Pibe : public Object {
	public:

	sf::Sprite sprite;

	Pibe(float x=0, float y=0) : Object({50.f,30.f}) {
		sprite.setTexture(assets::pibe);
		setX(x);
		setY(y);
		sprite.setOrigin(width()/2, height()/2);
	}

	void update(const float dt);
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
