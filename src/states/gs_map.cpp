#include <SFML/Graphics.hpp>

#include <iostream>
#include "paths.hpp"
#include "game_state.hpp"
#include "gs_map.hpp"
#include "line.hpp"

using namespace sf;

GameStateMap::GameStateMap (
	Game * g,
	node_graph gr,
	map<string,Vector2f> ps,
	vector<GameState*> mg) {

	game = g;
	graph = gr;
	positions = ps;

	// load map sprite 
	texture.loadFromFile(path::world);
	texture.setSmooth(true);
	sprite.setTexture(texture);

	// load character sprite
	character_texture.loadFromFile(path::run);
	character_texture.setSmooth(true);

	position = sprite.getPosition();

	// sæt minigames
	mini_games = mg;

	// start knude
	current_node = positions.begin()->first;
	target_node = current_node;
	character = new animation({0,1, 2, 3, 4, 5}, character_texture);
}

void GameStateMap::draw(const float dt) {
	// fjern advarsel om at dt ikke bliver brugt
	while (false) { auto i = dt; i = i;}

	// gør vinduet klar
	game->window.setView(view);
	game->window.clear(Color::Black);
	
	// tegn kortet
	game->window.draw(sprite);

	Font node_font;
	node_font.loadFromFile(path::font);
	t->setFont(node_font);

	// tegn alle knuder
	t->setColor(Color::Black);
	for (auto i : graph) {
		t->setString(i.first);
		auto p = positions[i.first] + position;
		t->setPosition(p);
		game->window.draw(*t);

		auto from = positions[i.first];

		// tegn alle kanter imellem knuderne
		for (auto j : i.second) {
			auto to = positions[j.first];

			auto start = from;
			auto end = to;
			if (start.x < end.x) continue;
			
			
			sfLine l(start, end);

			// skift farve, hvis en af siderne er den nuværende knude
			if (i.first == current_node) l.setColor(Color::Red);
			if (j.first == current_node) l.setColor(Color::Red);
			game->window.draw(l);
		}
	}
	

	t->setColor(Color::White);
	t->setString(current_node);
	t->setPosition(positions[current_node] + position);

	game->window.draw(*t);

	// tegn karakteren
	auto origin = positions[current_node];
	auto target = positions[target_node];
	auto path = target - origin;
	path.x *= route_position / delay;
	path.y *= route_position / delay;
	path += origin;

	game->window.draw(*character);
	character->setPosition(path + position);
}

void GameStateMap::update(const float dt) {

	if (route_position >= delay) {
		current_node = target_node;
		auto r = rand() % (mini_games.size());
		game->pushState(*(mini_games.begin() + r));
		route_position = 0.0;
	} else if (current_node != target_node)
		route_position += dt;

	character->update(dt);
}

void GameStateMap::handleInput() {
	Event event;
	constexpr float step_size = 5;
	float delta_x = 0;
	float delta_y = 0;

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

	// opdater kort position
	position.x += delta_x;
	position.y += delta_y;
	position.x = std::min(position.x, 0.0f);
	position.y = std::min(position.y, 0.0f);
	sprite.setPosition(position);

	// flyt til en anden knude
	if (target_node == current_node && new_route < graph[current_node].size() + 1) {
		auto new_node = graph[current_node].begin();

		for (size_t i = 0; i < new_route - 1; ++i) ++new_node;
		target_node = new_node->first;
	}
}

void GameStateMap::loadgame() {
	game->pushState(this);
}

void GameStateMap::reset() {
	
}

