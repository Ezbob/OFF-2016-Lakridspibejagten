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
	map<string, GameState*> mg,
	string start, string target) :
	graph(gr),
	positions(ps),
	current_node(start),
	target_node(start),
	end_node(target)
	{
	game = g;
	position = assets::world_sprite.getPosition();
	// sæt minigames
	mini_games = mg;
}

void GameStateMap::draw(const float dt) {
	// fjern advarsel om at dt ikke bliver brugt
	while (false) { auto i = dt; i = i;}


	// gør vinduet klar
	game->window.clear(Color::Black);
	
	auto size = game->window.getSize();
	// tegn kortet
	game->window.draw(assets::world_sprite);

	t->setFont(assets::font_main);

/******************************************************************************/
/* Tegn grafen                                                                */
/******************************************************************************/
	t->setColor(Color::Black);
	for (auto i : graph) {
		auto from = positions[i.first];

		// tegn alle kanter imellem knuderne
		for (auto j : i.second) {
			auto to = positions[j.first];
			Color edge_color = Color::Blue;
/**
	TODO: Gør start/end lidt mindre, så linjerne ikke rammer teksten
*/
			auto start = from;
			auto end = to;

			if (start.x < end.x) {
				start.x += 10;
				end.x -= 10;
			} else {
				start.x -= 10;
				end.x += 10;
			}
		
			if (start.y < end.y) {
				start.y += 10;
				end.y -= 10;
			} else {
				start.y -= 10;
				end.y += 10;
			}
			
			if (i.first == current_node || j.first == current_node)
				edge_color = Color::Red;

			sfLine l(start + position, end + position);
			l.setColor(edge_color);
			game->window.draw(l);
		}
	}

/******************************************************************************/
/* Tegn knuder                                                                */
/******************************************************************************/

	for (auto i : positions) {
		Color node_color = Color::Blue;
		t->setString(i.first);
		t->setPosition(i.second);
		if (i.first == current_node) node_color = Color::Red;
		if (i.first == end_node) node_color = Color::Green;
		t->setColor(node_color);
		game->window.draw(*t);
	}
/******************************************************************************/
/* Tegn løberen                                                               */
/******************************************************************************/
	game->window.draw(*assets::runner_animation);


/******************************************************************************/
/* Tegn valgmulighed                                                          */
/******************************************************************************/
	t->setString("");
	t->setCharacterSize(25);
	t->setPosition(10, size.y - t->getCharacterSize() - 5);
	int n = 0;

	for (auto i : graph[current_node]) {
		++n;
		t->setColor(Color::Blue);
		t->setString(std::to_string(n) + ": " + i.first);
		game->window.draw(*t);
		auto p = t->findCharacterPos(t->getString().getSize());
		p.x += 10;
		t->setPosition(p);
	}
}

void GameStateMap::update(const float dt) {

	if (route_position >= delay) {
		current_node = target_node;
		if (mini_games[current_node]) game->pushState(mini_games[current_node]);
		mini_games[current_node] = nullptr;
		route_position = 0.0;
	} else if (current_node != target_node)
		route_position += dt;

/******************************************************************************/
/* Opdater løberen                                                            */
/******************************************************************************/
	auto origin = positions[current_node];
	auto target = positions[target_node];
	auto path = target - origin;
	path.x *= route_position / delay;
	path.y *= route_position / delay;
	path += origin;
	assets::runner_animation->setPosition(path + position);
	assets::runner_animation->update(dt, 0.3);
}

void GameStateMap::handleInput() {
	Event event;
	constexpr float step_size = 5;
	float delta_x = 0;
	float delta_y = 0;

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
	assets::world_sprite.setPosition(position);

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

