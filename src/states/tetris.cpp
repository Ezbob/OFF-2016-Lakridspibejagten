#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tetris.hpp"

#include "data.h"

using namespace sf;
using namespace std;

static size_t x_offset = 0;
static size_t y_offset = 0;

int down;
int rotation;
int slide = 0;

typedef sf::Keyboard::Key key;

bool is_key_pressed(key k) {
	return sf::Keyboard::isKeyPressed(k);
}


template<class M>
int settle(M& world, M& block, size_t x, size_t y) {
	int lines = 0;
	for (size_t i = 0; i < block.size(); ++i)
	for (size_t j = 0; j < block[i].size(); ++j)
		if (block[i][j]) world[i + x][j + y] = block[i][j];

	for (size_t j = 0; j < world[0].size() - 1; ++j) {
		bool eliminate = true;
		for (size_t i = 1; i < world.size() - 1; ++i) {
			if (world[i][j] == 0){
				eliminate = false;
				break;
			}
		}

		if (eliminate) {
			++lines;
			for (size_t i = 1; i < world.size() - 1; ++i)
			for (size_t _j = j; _j; --_j)
				world[i][_j] = world[i][_j - 1];
		}
	}

	return lines;
}

auto new_matrix = [] (size_t m, size_t n) {
	GameStateTetris::matrix mat;
	mat.resize(m);
	for (size_t i = 0; i < m; ++i)
		mat[i].resize(n);
	return mat;
};

GameStateTetris::matrix new_block() {
	auto m = new_matrix(4,4);
	size_t b = rand() % 7;

	for (size_t i = 0; i < 4; ++i)
	for (size_t j = 0; j < 4; ++j)
		m[i][j] = blocks[b][i][j];

	return m;
}

GameStateTetris::GameStateTetris(Game * g) {
	game = g;
	reset();
}

void GameStateTetris::reset() {
	world = new_matrix(world_width, world_height);

	/* lav en dummy kant */
	for (size_t i = 0; i < world_height; ++i) {
		world[0][i] = 1;
		world[world_width - 1][i] = 1;
	}
	
	for (size_t i = 0; i < world_width; ++i)
		world[i][world_height - 1] = 1;

	current_block = new_block();
	next_block = new_block();

	x = world_width / 2;
	y = 0;
	settled = false;
	get_new_block = false;
}

void GameStateTetris::draw_matrix(GameStateTetris::matrix block, size_t x, size_t y, sf::Color c) {

	sf::RectangleShape rectangle;

	for (size_t i = 0; i < block.size(); ++i)
	for (size_t j = 0; j < block[i].size(); ++j) {
		rectangle.setPosition(x + i * tile_dim.x, y + j * tile_dim.y);
		rectangle.setSize(tile_dim);
		rectangle.setFillColor(c);
		if (block[i][j]) game->window.draw(rectangle);
	}
}

void GameStateTetris::draw(const float dt) {
	game->window.clear(Color::White);
	draw_matrix(world, x_offset, y_offset, Color::Blue);
	draw_matrix(current_block, x * tile_dim.x + x_offset, y * tile_dim.y + y_offset, Color::Red);
	draw_matrix(next_block, (world_width + 2) * tile_dim.x + x_offset, (world_height / 2 - 2) * tile_dim.y + y_offset, Color::Red);

}

bool collides(GameStateTetris::matrix block, GameStateTetris::matrix world, size_t x, size_t y) {
	for (size_t i = 0; i < block.size(); ++i)
	for (size_t j = 0; j < block[i].size(); ++j)
		if (block[i][j] && world[i + x][j + y]) return true;

	return false;
}

void GameStateTetris::update(const float dt) {

	static double time = 0.0;
	static double delay = 0.8;
	static double input_delay = 0.10;
	static double input_time = 0.0;

	auto dimensions = game->window.getSize();

	tile_dim.x = (dimensions.x  / 2) / world_width;
	tile_dim.y = dimensions.y / world_height;

	dimensions.x /= 2;
	dimensions.x -= (tile_dim.x * world_width) / 2;

	x_offset = dimensions.x;
	y_offset = 0;

	time += dt;
	input_time += dt;

	if (input_time > input_delay) {
	
		input_time -= input_delay;

		if (down) {
			if (!collides(current_block, world, x, y + 1))
				++y;
			else
				settled = true;
		}

		if (!settled) {
			if (!collides(current_block, world, x + slide, y))
				x += slide;

			if (rotation) {
				auto b = new_matrix(4, 4);

				for (size_t i = 0; i < 4; ++i)
				for (size_t j = 0; j < 4; ++j)
					b[i][j] = current_block[j][3 - i];

				if (collides(b, world, x, y) == false)
					current_block = b;
			}
		}
	}

	if (time > delay) {

		time -= delay;

		if (!settled) {
			if (!collides(current_block, world, x, y + 1))
				++y;
			else
				settled = true;
		}
	}

	// kopier blokken ind i world og tjek om der er nogen af de berørte linjer der er færdige
	if (settled) {
		if (y == 0) game->popState();
		get_new_block = true;
		game->score_pibe += settle(world, current_block, x, y);
		x = world_width / 2;
		y = 0;
	}

	// lav en ny blok
	if (get_new_block) {
		current_block = next_block;
		next_block = new_block();
	}

	if (settled) delay *= 0.95;

	slide = 0;
	down = 0;
	rotation = 0;
	get_new_block = false;
	settled = false;
}

void GameStateTetris::handleInput() {
	Event e;

	while (game->window.pollEvent(e));

	if (is_key_pressed(Keyboard::Escape)) game->popState();
	if (is_key_pressed(Keyboard::Right)) slide = 1;
	if (is_key_pressed(Keyboard::Left))  slide = -1;
	if (is_key_pressed(Keyboard::Up))    rotation = 1;
	if (is_key_pressed(Keyboard::Down))  down = 1;
}

