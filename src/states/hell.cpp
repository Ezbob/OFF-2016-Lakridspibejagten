#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "hell.hpp"

using namespace std;
using namespace sf;

struct ship : public sf::Sprite {
	int hits;
};

struct bullet : public sf::Sprite {

};

std::vector<bullet> bullets;
std::vector<ship> ships;
ship player;

bool collides(sf::Vector2f a, sf::Vector2f b, double r) {
	Vector2f delta = a - b;
	delta.x *= delta.x;
	delta.y *= delta.y;
	auto dr = delta.x + delta.y;
	return dr < r * r;
}

hell::hell(Game* g) {
	game = g;
}

void hell::reset() {

}

void hell::draw(double dt) {
	do_nothing(dt);

}

void hell::update(double dt) {
	do_nothing(dt);

	for (auto b : bullets) {
		for (auto s : ships ) {
//			collides(*b, *s, 10.0f);
		}
			
	}
}

void hell::handle_input() {

}

