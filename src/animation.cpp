#include <iostream>

#include "animation.hpp"

animation::animation(std::vector<int> frame_indices, sf::Texture& t) {
	this->frame_indices = frame_indices;
	setupFrames(t);
}

void animation::setupFrames(sf::Texture& t) {
	auto size = t.getSize();
	width = size.x / frame_indices.size();
	auto r = getTextureRect();
	r.width = width;
	setTextureRect(r);
	frame = 0;
}

void animation::update(double dt) {
	update(dt, 0.2);
}

void animation::update(double dt, double ts) {
	static double time = 0.0;
	time += dt;

	if (time > ts) {
		time = 0.0;
		nextFrame();
	}
}

void animation::nextFrame() {
	frame = (frame+1) % frame_indices.size();
	setFrame(frame);
}

void animation::setFrame(int findex) {
	size_t index = frame_indices[findex];
	auto rect = getTextureRect();
	rect.left = index * width;
	setTextureRect(rect);
}

int animation::getFrame() {
	return frame;
}

