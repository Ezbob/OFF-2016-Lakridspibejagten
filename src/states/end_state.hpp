#ifndef UUID_030E816C_6EC8_49B8_A2E0_A6A2E0C7A536
#define UUID_030E816C_6EC8_49B8_A2E0_A6A2E0C7A536

#include <SFML/Graphics.hpp>
#include "game_state.hpp"

class end_state : public GameState, public sf::Texture {
public:
	end_state(Game * g);
	void draw(float const dt);
	void update(float const dt);
	void handleInput();
};

#endif
