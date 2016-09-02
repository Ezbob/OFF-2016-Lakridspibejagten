#include <iostream>

#include "animation.hpp"

animation::animation(std::vector<int> frame_indices, sf::Texture& t, int w) {
	this->frame_indices = frame_indices;
	setupFrames(t, w);
}

void animation::update(double dt, double ds) {
	static double time = 0.0;
	time += dt;

	if (time > ds) {
		++frame;
		time = 0.0;
		size_t index = frame_indices[frame % frame_indices.size()];
		auto rectangle = getTextureRect();
		rectangle.left = index * width;
		setTextureRect(rectangle);
	}
}

void animation::setupFrames(sf::Texture& t, int w) {
	setTexture(t);
	auto size = t.getSize();
	if (w == 0)
		width = size.x / frame_indices.size();
	else
		width = w;

	auto r = getTextureRect();
	r.width = width;
	setTextureRect(r);
	frame = 0;
}

void animation::setFrameOffset(int index) {
	auto rect = getTextureRect();
	rect.left = index * width;
	setTextureRect(rect);
}

