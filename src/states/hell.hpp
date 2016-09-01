#ifndef UUID_7E5B253A_A93D_4558_A867_EB56AC72F2BD
#define UUID_7E5B253A_A93D_4558_A867_EB56AC72F2BD

#include "game_state.hpp"

class hell : public GameState {
public:
	hell(Game* g);
	void reset();
	void draw(double dt);
	void update(double dt);
	void handle_input();
};

#endif
