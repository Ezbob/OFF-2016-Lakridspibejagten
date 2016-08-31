#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "gs_map.hpp"

using namespace sf;

void GameStateMap::draw(const float dt) {
	game->window.setView(view);
	game->window.clear(Color::Black);
	game->window.draw(sprite);
}

void GameStateMap::update(const float dt) {
	
}

void GameStateMap::handleInput() {
	Event event;

	constexpr float step_size = 5;
	while (game->window.pollEvent(event)) {
		switch (event.type) {
			case Event::Closed: {
				game->window.close();
				break;
			}

			case Event::KeyPressed: {
				switch (event.key.code) {
				case Keyboard::Escape:
					game->window.close();
					break;
				
				case Keyboard::Left:
					position.x -= step_size;
					break;
				
				case Keyboard::Right:
					position.x += step_size;
					break;

				case Keyboard::Up:
					position.y -= step_size;
					break;

				case Keyboard::Down:
					position.y += step_size;
					break;

				default:
					break;
				}
			}

			default:
				break;
		}
	}

#if 0
	auto rectangle = texture.getSize();
	position.x = std::max(std::min(0.0f, position.x), float(rectangle.x));
	position.y = std::max(std::min(0.0f, position.y), float(rectangle.y));
#endif
	sprite.setPosition(position);

}

void GameStateMap::loadgame() {
	game->pushState(this);
}	

