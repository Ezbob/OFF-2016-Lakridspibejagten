#include <SFML/Graphics.hpp>

#include <iostream>
#include "gs_map.hpp"
#include "line.hpp"
#include "assets.hpp"

using namespace sf;

sf::Color base_color     = Color(255, 0xa0, 0x00);
sf::Color current_color  = Color(0x00, 0x00, 0xff);
sf::Color inactive_color = Color(0xA0, 0xA0, 0xA0);
sf::Color target_color   = Color(0x00, 0xff, 0x00);

GameStateMap::GameStateMap (
	Game * g,
	node_graph gr,
	map<string,Vector2f> ps,
	map<string, GameState*> mg,
	string start, string target) :
	graph(gr),
	positions(ps),
	current_node(start),
	target_node(start),
	end_node(target)
	{
	game = g;
	// sæt minigames
	mini_games = mg;

	assets::world_sprite.setScale({2.f,2.f});
}

void GameStateMap::draw(const float dt) {
	do_nothing(dt);

	// gør vinduet klar
	game->window.clear(Color::Black);
	game->window.draw(assets::world_sprite);
	t->setFont(assets::font_main);

/******************************************************************************/
/* Tegn grafen                                                                */
/******************************************************************************/

#if 0		// tegn alle kanter imellem knuderne
	for (auto i : graph) {
		auto from = positions[i.first];
		t->setString(i.first);
		t->setPosition(0,0);
		auto a = t->findCharacterPos(t->getString().getSize());

		for (auto j : i.second) {
			t->setString(j.first);
			t->setPosition(0,0);
			auto b = t->findCharacterPos(t->getString().getSize());
			auto to = positions[j.first];
			if (from.y < to.y) continue;
			Color edge_color = base_color;
/**
	TODO: Gør start/end lidt mindre, så linjerne ikke rammer teksten
*/
			auto start = from;
			auto end = to;

			if (i.first == current_node || j.first == current_node)
				edge_color = current_color;

			if (j.second < 0) edge_color = inactive_color;

			start.y -= 5;
			if (from.x < to.x) start.x += a.x / 2;

			end.y += t->getCharacterSize() + 5;
			if (to.x < from.x) end.x += b.x / 2;

			sfLine l(start, end);
			
			
			
			l.setColor(edge_color);
			game->window.draw(l);
		}
	}

/******************************************************************************/
/* Tegn knuder                                                                */
/******************************************************************************/

	for (auto i : positions) {
		Color node_color = base_color;
		for (auto p : graph[i.first]) if (p.second < 0) node_color = inactive_color;
		t->setString(i.first);
		t->setPosition(i.second);
		auto p = t->findCharacterPos(t->getString().getSize());
		if (i.first == current_node) node_color = current_color;
		if (i.first == end_node) node_color = target_color;
		t->setColor(node_color);
		game->window.draw(*t);
	}

/******************************************************************************/
/* Tegn løberen                                                               */
/******************************************************************************/


/******************************************************************************/
/* Tegn valgmulighed                                                          */
/******************************************************************************/
	t->setString("");
	t->setCharacterSize(25);
	t->setPosition(10, size.y - t->getCharacterSize() - 5);
	int n = 0;

	for (auto i : graph[current_node]) {
		++n;

		Color col = base_color;
		if (i.second < 0) col = inactive_color;
		if (i.first == end_node) col = target_color;

		t->setString(std::to_string(n) + ": " + i.first);

		t->setColor(col);
		game->window.draw(*t);
		auto p = t->findCharacterPos(t->getString().getSize());
		p.x += 10;
		t->setPosition(p);
	}
#endif
	game->window.draw(*assets::runner_animation);
}

void GameStateMap::update(const float dt) {

	if (route_position >= delay) {
		graph[current_node][target_node] = -1;
		graph[target_node][current_node] = -1;
		current_node = target_node;
		if (mini_games[current_node]) game->pushState(mini_games[current_node]);
		mini_games[current_node] = nullptr;
		route_position = 0.0;
		target_node = graph[current_node].begin()->first;
	} else if (current_node != target_node)
		route_position += dt;
	else {
		route_position = 0;
	}
/******************************************************************************/
/* Opdater løberen                                                            */
/******************************************************************************/
	auto origin = positions[current_node];
	auto target = positions[target_node];
	auto path = target - origin;
	path.x *= route_position / delay;
	path.y *= route_position / delay;
	path += origin;
	assets::runner_animation->setPosition(path);
	assets::runner_animation->update(dt, 0.3);
}

void GameStateMap::handleInput() {
	Event event;

	size_t new_route = 11;

	if (current_node == end_node) {
		game->popState();
		return;
	}
	while (game->window.pollEvent(event)) {
		switch (event.type) {
			case Event::Closed:
				game->window.close();
			break;

			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					game->window.close();

				if (event.key.code >= Keyboard::Num0 &&
				    event.key.code <= Keyboard::Num9) {
				    new_route = (event.key.code - Keyboard::Num0);
				}
				if (event.key.code == Keyboard::Space)
					new_route = 1;

			break;

			default:
			break;
		}
	}

	// flyt til en anden knude
	if (target_node == current_node && new_route < graph[current_node].size() + 1) {

		auto new_node = graph[current_node].begin();

		for (size_t i = 0; i < new_route - 1; ++i) ++new_node;
		if (new_node->second >= 0)
			target_node = new_node->first;
	}
}

void GameStateMap::loadgame() {
	game->pushState(this);
}

void GameStateMap::reset() {
	
}

