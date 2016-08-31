#include <iostream>

#include "animation.hpp"

animation::animation(std::vector<int> frame_indices, sf::Texture& t) {
	this->frame_indices = frame_indices;
	setTexture(t);
	auto size = t.getSize();
	width = size.x / frame_indices.size();

	auto r = getTextureRect();
	r.width = width;
	setTextureRect(r);
	std::cout << frame_indices.size() << "\n";
	frame = 0;
}

void animation::update(double dt) {
	static double time = 0.0;
	time += dt;

	if (time > 0.2) {
		++frame;
		time = 0.0;
		size_t index = frame_indices[frame % frame_indices.size()];
		auto rectangle = getTextureRect();
		rectangle.left = index * width;
		setTextureRect(rectangle);
	}
}

