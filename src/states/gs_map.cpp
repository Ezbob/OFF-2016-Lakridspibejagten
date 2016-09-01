#include <SFML/Graphics.hpp>

#include <iostream>
#include "gs_map.hpp"
#include "line.hpp"
#include "assets.hpp"

using namespace sf;

GameStateMap::GameStateMap (
	Game * g,
	node_graph gr,
	map<string,Vector2f> ps,
	map<string, GameState*> mg) :
	character({0,1,2,3,4,5}, assets::runner),
	graph(gr),
	positions(ps)
	{
	game = g;
	sprite.setTexture(assets::world);

	// load character sprite
	position = sprite.getPosition();

	// sæt minigames
	mini_games = mg;

	// start knude
	current_node = positions.begin()->first;
	target_node = current_node;
}

void GameStateMap::draw(const float dt) {
	// fjern advarsel om at dt ikke bliver brugt
	while (false) { auto i = dt; i = i;}

	// gør vinduet klar
	game->window.clear(Color::Black);
	
	// tegn kortet
	game->window.draw(sprite);

	t->setFont(assets::font_main);

/******************************************************************************/
/* Tegn grafen                                                                */
/******************************************************************************/
	t->setColor(Color::Black);
	for (auto i : graph) {

		t->setString(i.first);
		auto p = positions[i.first] + position;
		t->setPosition(p);

		if (i.first == current_node) t->setColor(Color::White);
		else t->setColor(Color::Black);
		auto edge_color = i.first == current_node ? Color::Blue : Color::Red;
		game->window.draw(*t);

		auto from = positions[i.first];

		// tegn alle kanter imellem knuderne
		for (auto j : i.second) {
			auto to = positions[j.first];

			auto start = from;
			auto end = to;
			if (start.x < end.x) continue;

			sfLine l(start, end);
			l.setColor(edge_color);
			game->window.draw(l);
		}
	}

/******************************************************************************/
/* Tegn manden                                                                */
/******************************************************************************/
	auto origin = positions[current_node];
	auto target = positions[target_node];
	auto path = target - origin;
	path.x *= route_position / delay;
	path.y *= route_position / delay;
	path += origin;

	game->window.draw(character);
	character.setPosition(path + position);
}

void GameStateMap::update(const float dt) {

	if (route_position >= delay) {
		current_node = target_node;
		if (mini_games[current_node]) game->pushState(mini_games[current_node]);
		mini_games[current_node] = nullptr;
		route_position = 0.0;
	} else if (current_node != target_node)
		route_position += dt;

	character.update(dt);
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

