#ifndef UUID_8BEA4952_65F7_4D2D_B7D2_9E861EC13085
#define UUID_8BEA4952_65F7_4D2D_B7D2_9E861EC13085

#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "assets.hpp"

class GameStateSplash: public GameState {
protected:
	sf::Sprite back;
	int frame{0};
	double time{0.0};
	sf::IntRect back_rect;

public:
	GameStateSplash(Game *g) : back_rect(0,0,400,300) {
		game = g;

		back.setTexture(assets::splash);
		back.setScale({2.f, 2.f});
	}

	void draw(const float dt);
	void update(const float dt);
	void handleInput();
};

#endif
