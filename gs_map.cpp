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
	Font f;
	f.loadFromFile("/usr/share/wine/fonts/arial.ttf");
	t->setFont(f);

	for (auto i : graph) {
		t->setString(i.first);
		t->setPosition(positions[i.first]);
		game->window.draw(*t);
	}

	delete t;
}

void GameStateMap::update(const float dt) {
	
}

void GameStateMap::handleInput() {
	Event event;
	constexpr float step_size = 5;
	float delta_x = 0;
	float delta_y = 0;
	float scale = 1.0;
	static float scale_x = 1.0;
	static float scale_y = 1.0;

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

	auto texture_size = texture.getSize();
	auto window_size  = game->window.getSize();
	scale_x = min(scale_x * scale, float(window_size.x) / texture_size.x);
	scale_y = min(scale_y * scale, float(window_size.x) / texture_size.x);

	sprite.setScale(Vector2f(scale_x, scale_y));
	sprite.setPosition(position);
}

void GameStateMap::loadgame() {
	game->pushState(this);
}	

