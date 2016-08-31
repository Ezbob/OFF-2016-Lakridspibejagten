#include <SFML/Graphics.hpp>

#include <iostream>

#include "game_state.hpp"
#include "gs_map.hpp"
#include "line.hpp"

using namespace sf;

void GameStateMap::draw(const float dt) {
	game->window.setView(view);
	game->window.clear(Color::Black);
	game->window.draw(sprite);
	Text * t = new Text();
	Font node_font;
	node_font.loadFromFile("./AmazDooMLeft.ttf");
	t->setFont(node_font);

	for (auto i : graph) {
		if (current_node == "") current_node = i.first;
		t->setString(i.first);
		t->setPosition(positions[i.first] + position);
		game->window.draw(*t);
		for (auto j : i.second) {
			sfLine l(positions[i.first] + position, positions[j.first] + position);
			game->window.draw(l);
		}
	}


	t->setColor(Color::Black);
	t->setString(current_node);
	t->setPosition(positions[current_node] + position);
	game->window.draw(*t);

	delete t;
}

void GameStateMap::update(const float dt) {
	
}

void GameStateMap::handleInput() {
	Event event;
	constexpr float step_size = 5;
	float delta_x = 0;
	float delta_y = 0;
	static float scale = 1.0;

	size_t new_route = 11;
	while (game->window.pollEvent(event)) {
		switch (event.type) {
			case Event::Closed:
				game->window.close();
			break;

			case Event::MouseWheelMoved:
				if (event.mouseWheel.delta > 0) scale *= 2.0;
				if (event.mouseWheel.delta < 0) scale /= 2.0;
			break;

			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					game->window.close();

				if (event.key.code >= Keyboard::Num0 &&
				    event.key.code <= Keyboard::Num9) {
				    new_route = (event.key.code - Keyboard::Num0);
				}

			break;

			default:
			break;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Up)) delta_y = step_size;
	if (Keyboard::isKeyPressed(Keyboard::Down)) delta_y = -step_size;
	if (Keyboard::isKeyPressed(Keyboard::Left)) delta_x = step_size;
	if (Keyboard::isKeyPressed(Keyboard::Right)) delta_x = -step_size;

	position.x += delta_x;
	position.y += delta_y;
	position.x = std::min(position.x, 0.0f);
	position.y = std::min(position.y, 0.0f);

	sprite.setPosition(position);
	if (new_route < 11 && new_route < graph[current_node].size() + 1) {
		std::cerr << "new route = " << new_route << "\n";
		auto new_node = graph[current_node].begin();
		for (size_t i = 0; i < new_route - 1; ++i)
			++new_node;
		current_node = new_node->first;
		auto r = rand() % (mini_games.size());
		game->pushState(*(mini_games.begin() + r));
	}
	
}

void GameStateMap::loadgame() {
	game->pushState(this);
}	

