#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tetris.hpp"

#include "game.hpp"
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
	int c = color[rand() % 3 + 2];
	for (size_t i = 0; i < 4; ++i)
	for (size_t j = 0; j < 4; ++j)
		m[i][j] = blocks[b][i][j] * c;

	return m;
}

GameStateTetris::GameStateTetris(Game * g) {
	game = g;
	frame_texture.loadFromFile("assets/imgs/arcade_screen.png");
	foreground.setTexture(frame_texture);
	foreground.setPosition(0.f,0.f);
	foreground.setScale({2.f, 2.f});
	reset();
}

void GameStateTetris::reset() {
	world = new_matrix(world_width, world_height);

	/* lav en dummy kant */
	for (size_t i = 0; i < world_height; ++i) {
		world[0][i] =  0x0000ffff;
		world[world_width - 1][i] = 0x0000ffff;
	}
	
	for (size_t i = 0; i < world_width; ++i)
		world[i][world_height - 1] = 1;

	current_block = new_block();
	next_block = new_block();

	x = world_width / 2 - 2;
	y = 0;
	settled = false;
	get_new_block = false;
}

void GameStateTetris::draw_matrix(GameStateTetris::matrix block, int x, int y, double bounce) {

	sf::RectangleShape rectangle;

	for (size_t i = 0; i < block.size(); ++i)
	for (size_t j = 0; j < block[i].size(); ++j) {
		if (block[i][j]) {
			auto size = tile_dim;
			size.x *= bounce;
			size.y *= bounce;
			auto position = Vector2f(x + i * tile_dim.x - (size.x - tile_dim.x) / 2, y + j * tile_dim.y - (size.y - tile_dim.y) / 2);
			
			rectangle.setPosition(position);
			rectangle.setSize(size);
			rectangle.setFillColor(Color(block[i][j]));
			game->window.draw(rectangle);

		}
	}
}

void GameStateTetris::draw(const float dt) {
	//do_nothing(dt);


	game->window.clear(Color::White);

	sf::RectangleShape rectangle;
	rectangle.setFillColor(Color(0x80, 0x80, 0x80));
	rectangle.setPosition(x_offset, y_offset);
	rectangle.setSize(Vector2f(tile_dim.x * world_width, tile_dim.y * world_height));
	game->window.draw(rectangle);

	draw_matrix(world, x_offset, y_offset);
	draw_matrix(current_block, x * tile_dim.x + x_offset, y * tile_dim.y + y_offset, bounce);
	draw_matrix(next_block, (world_width + 2) * tile_dim.x + x_offset, (world_height / 2 - 2) * tile_dim.y + y_offset);
	game->window.draw(this->foreground);
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
	static double input_delay = 0.00;
	static double input_time = 0.0;


	tile_dim.x = (WINDOW_WIDTH / 2) / world_width;
	tile_dim.y = WINDOW_HEIGHT / world_height;

	x_offset = (WINDOW_WIDTH - tile_dim.x * world_width) / 2;
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
		auto increase = settle(world, current_block, x, y);
		game->score_gave |= (increase > 1);
		game->score_pibe += increase;
	}

	// lav en ny blok
	if (get_new_block) {
		x = world_width / 2 - 2;
		y = 0;
		current_block = next_block;
		next_block = new_block();
	}

	if (settled) delay *= 0.95;

	slide = 0;
	down = 0;
	rotation = 0;
	get_new_block = false;
	settled = false;
	
	bounce *= 1.01;
	if (bounce > 1.25) bounce = 1.0;
}

void GameStateTetris::handleInput() {
	Event e;

	while (game->window.pollEvent(e)) {
		if (is_key_pressed(Keyboard::Escape)) game->popState();
		if (is_key_pressed(Keyboard::Right)) slide = 1;
		if (is_key_pressed(Keyboard::Left))  slide = -1;
		if (is_key_pressed(Keyboard::Up))    rotation = 1;
		if (is_key_pressed(Keyboard::Down))  down = 1;
	}
}

