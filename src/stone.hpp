#ifndef UUID_AF6E1164_EF92_4063_B04E_BEAB64730646
#define UUID_AF6E1164_EF92_4063_B04E_BEAB64730646

#include <SFML/Graphics.hpp>
#include "object.hpp"

class Stone : public Object {
	public:

	sf::Vector2f velocity{-5, 0};
	sf::Texture tex;
	sf::Sprite sprite;
	//sf::RectangleShape rectShape;

	//float width{24},
	//	  height{24};
	float speed{.2};

	Stone(float x, float y) : Object ({24, 12}) {
		if (!tex.loadFromFile("assets/imgs/rock1.png"))
			std::cerr << "Error loading rock texture" << std::endl;
		sprite.setTexture(tex);
		//sprite.setPosition({x, y});
		setX(x);
		setY(y);
		sprite.setOrigin(width()/2, height()/2);
		scale(2.f, 2.f);
		/*
		rectShape.setSize({width, height});
		rectShape.setOutlineColor(sf::Color::Red);
		rectShape.setOutlineThickness(1);
		rectShape.setOrigin(width/2, height/2);
		rectShape.setPosition(x, y);
		*/
	}

	void update(const float dt);
	void reset();
	void scale(float sx, float sy);
	void setVelocity(float vx, float vy);
	void draw(sf::RenderWindow &window);
	
	/*
	float x()		 { return sprite.getPosition().x; }
	float y()		 { return sprite.getPosition().y; }
	float left()	 { return x() - width / 3; }
	float right()	 { return x() + width / 3; }
	float top()		 { return y() - height / 6; }
	float bottom()	 { return y() + height / 2; }
	*/
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
