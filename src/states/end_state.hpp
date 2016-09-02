#ifndef UUID_030E816C_6EC8_49B8_A2E0_A6A2E0C7A536
#define UUID_030E816C_6EC8_49B8_A2E0_A6A2E0C7A536

#include <SFML/Graphics.hpp>
#include "game_state.hpp"

class end_state : public GameState, public sf::Texture {
public:

	sf::Sprite back;
	sf::Text textTop,
			 textBottom;
	sf::IntRect back_rect;
	unsigned int frame{0};
	double time{0.f};
	int state{0}; // 0: undetermined, 1: won, 2: lose
	bool show_texture{false};

	end_state(Game * g);
	void draw(float const dt);
	void update(float const dt);
	void handleInput();

	void draw_summary(float const dt);
	void draw_texture(float const dt);

	bool has_won();
};

#endif
