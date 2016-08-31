#include <iostream>
#include <cstring>
#include <cstddef>
#include <chrono>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>

#include "data.h"

typedef sf::Keyboard::Key key;

#define NDEBUG

#ifndef NDEBUG
#define DEBUG std::cerr << "\r" << __func__ << " " << __LINE__
#else
#define DEBUG do {} while(0)
#endif

bool is_key_pressed(key k) {
	return sf::Keyboard::isKeyPressed(k);
}

auto matrix = [] (size_t w, size_t h) {
	DEBUG;
	std::vector<std::vector<int>> m (w);
	for (size_t i = 0; i < w; ++i)
		m[i].resize(h);
	DEBUG;
	return m;
};

sf::RenderWindow tetris(sf::VideoMode(width * tile_dim.x, height * tile_dim.y), "Tetris (y)Bearmode");

auto new_block() -> decltype(matrix(0,0)) {
	DEBUG;
	auto b = matrix(4,4);
	int id = rand() % 7; // 5 typer blokke
	int c  = rand() % 3 + 2; // 5 typer farver
	DEBUG;
	for (size_t i = 0; i < 4; ++i)
	for (size_t j = 0; j < 4; ++j)
		b[i][j] = blocks[id][i][j] * color[c];
	DEBUG;
	return b;
}

template<class T>
void draw_matrix(T m, int offset_x, int offset_y, double bounce) {
	DEBUG;
	auto dim = tile_dim;
	dim.x *= bounce;
	dim.y *= bounce;
	auto rectangle = sf::RectangleShape(dim);

	for (size_t i = 0; i < m.size(); ++i)
	for (size_t j = 0; j < m[i].size(); ++j) {
		DEBUG;
		if (m[i][j] != 0) {
			rectangle.setFillColor(sf::Color(m[i][j]));
			rectangle.setPosition(
				(offset_x + i) * tile_dim.x  + (tile_dim.x - dim.x) / 2,
				(offset_y + j) * tile_dim.y  + (tile_dim.y - dim.y) / 2
				);

			tetris.draw(rectangle);
		}
	}
	DEBUG;
}

template<class M>
bool collides(M world, M block, int x, int y) {
	DEBUG;

	for (size_t i = 0; i < block.size(); ++i)
	for (size_t j = 0; j < block[i].size(); ++j) {
		DEBUG;
		if (block[i][j] == 0) continue;
		if (x + i >= world.size() || y + j >= world[x + i].size()) continue;
		if (world[x + i][y + j]) return true;
	}
	DEBUG;
	return false;
}

template<class M>
void rotate(M & block) {
	DEBUG;
	M b = matrix(block.size(), block.size());

	for (size_t i = 0; i < b.size(); ++i)
	for (size_t j = 0; j < b.size(); ++j)
		b[i][j] = block[j][b.size() - 1 - i];
	DEBUG;
	block = b;
	DEBUG;

}
auto reset = [] () {
	auto w = matrix(width, height);
	DEBUG;

	for (size_t i = 0; i < width; ++i) {
		w[i][height - 1] = color[1];
	}
	DEBUG;

	for (size_t i = 0; i < height; ++i) {
		w[0][i] = color[1];
		w[width - 1][i] = color[1];
	}
	DEBUG;

	return w;
};

template<class M>
void settle(M& world, M& block, size_t x, size_t y) {
	DEBUG;
	for (size_t i = 0; i < block.size(); ++i)
	for (size_t j = 0; j < block[i].size(); ++j)
		if (block[i][j]) world[i + x][j + y] = block[i][j];
	DEBUG;

	if (y <= 0) {
		std::cout << "game over\n";
		world = reset();
	}
	DEBUG;

	for (size_t j = 0; j < world[0].size() - 1; ++j) {
		bool eliminate = true;
	DEBUG;
		for (size_t i = 1; i < world.size() - 1; ++i) {
			if (world[i][j] == 0){
				eliminate = false;
				break;
			}
		}
	DEBUG;

		if (eliminate) {
			for (size_t i = 1; i < world.size() - 1; ++i)
			for (size_t _j = j; _j; --_j)
				world[i][_j] = world[i][_j - 1];
		}
	DEBUG;
	}
	DEBUG;

	block = new_block();
	DEBUG;
}

int main() {
	using namespace sf;
	using namespace std::chrono;

	auto now = []() { return std::chrono::steady_clock::now(); };

	auto world = reset();
	auto block = new_block();

	size_t x = (world.size() - block.size()) / 2;
	size_t y = 0;

	std::ifstream config("config.txt");
	sf::Texture background_texture;
	sf::Texture frame_texture;
	sf::Sprite background;
	sf::Sprite frame;

	int background_y = 0;
	{
		std::string name;
		config >> name;
		background_texture.loadFromFile(name.c_str());
		background_texture.setRepeated(true);
		background_texture.setSmooth(true);
		background.setTexture(background_texture, true);
		auto width_scale = background_texture.getSize().x / tetris.getSize().x;
		auto height_scale = background_texture.getSize().y / tetris.getSize().y;
		auto scale = std::min(width_scale, height_scale);
		background.setScale(scale, scale);
	}

	{
		std::string name;
		config >> name;
		frame_texture.loadFromFile(name.c_str());
		frame_texture.setRepeated(false);
		frame_texture.setSmooth(true);		
		frame.setTexture(frame_texture);
		auto dims = frame_texture.getSize();
		frame.setScale(double(tile_dim.x) / dims.x, double(tile_dim.y) / dims.y);
	}

	tetris.setFramerateLimit(20);

	auto input_counter = now();
	auto drop_counter = now();
	auto bounce = 1.0;
	auto bounce_scale = 1.05;
	while (tetris.isOpen()) {
		Event e;
		while(tetris.pollEvent(e));
		bool settled = false;
		background.setTextureRect(IntRect(0,background_y, background_texture.getSize().x, background_y + background_texture.getSize().y));
		background_y++;


		auto time = now();
		auto seed = time - input_counter;
		srand(seed.count());
		if (is_key_pressed(key::Escape)) {
			tetris.close();
			continue;
		}

		if (time - input_counter > 100ms) {
			if (is_key_pressed(key::Left))
				x -= !collides(world, block, x - 1, y);

			if (is_key_pressed(key::Right))
				x += !collides(world, block, x + 1, y);

			if (is_key_pressed(key::Up)) {
				auto b = block;
				rotate(block);
				if (collides(world, block,x ,y)) {
					block = b;
				}
			}

			if (is_key_pressed(key::Down)) {
				if (collides(world, block, x, y + 1))
					settled = true;
				else
					y++;
			}
			input_counter = time;
			if (bounce > 1.25)
				bounce = 1.0;
			bounce *= bounce_scale;
		}

		if (time - drop_counter > 400ms) {
			if (collides(world, block, x, y + 1))
				settled = true;
			else
				y++;
			drop_counter = time;
		}

		tetris.clear();
		tetris.draw(background);

			draw_matrix(world, 0, 0, 1.0);
			draw_matrix(block, x, y, bounce);

		for (size_t i = 0; i < world.size(); ++i) {
			frame.setPosition(i * tile_dim.x, tetris.getSize().y - tile_dim.y);
			tetris.draw(frame);
		}

		for (size_t i = 0; i < world[0].size() - 1; ++i) {
			frame.setPosition(0, i * tile_dim.y);
			tetris.draw(frame);
			frame.setPosition(tetris.getSize().x - tile_dim.x, i * tile_dim.y);
			tetris.draw(frame);
		}

		tetris.display();

		if (settled) {
			bounce = 2.0;
			settle(world, block, x, y);
			y = 0;
			x = (world.size() - block.size()) / 2;
		}
	}
}
