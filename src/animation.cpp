#include "animation.hpp"

animation::animation(std::vector<int> frame_indices, sf::Texture t) {
	this->frame_indices = frame_indices;
	width = t.getSize().x;
	height = t.getSize().y;
	setTexture(t);
	frame = 0;
	update();
}

void animation::update() {
	auto rectangle = sf::IntRect(frame_indices[frame] *  width, 0, (frame_indices[frame] + 1) *  width, height);
	setTextureRect(rectangle);
	++frame;
}

