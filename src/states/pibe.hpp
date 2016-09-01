#ifndef UUID_EF098647_2504_40B0_9E44_A8F183DD17B2
#define UUID_EF098647_2504_40B0_9E44_A8F183DD17B2

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "assets.hpp"

class Pibe : public Object {
	public:

	sf::Sprite sprite;

	Pibe(float x, float y) : Object({50.f,30.f}) {
	}

	void update(const float dt);

};

#endif
