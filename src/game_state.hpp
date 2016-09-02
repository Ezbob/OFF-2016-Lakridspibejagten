#ifndef UUID_D4B20B8C_0C1C_46E2_BDD3_611C34E450FC
#define UUID_D4B20B8C_0C1C_46E2_BDD3_611C34E450FC

#include "game.hpp"

class GameState {
protected:
	virtual void do_nothing(double const d) {
		if (d != 0) do_nothing(0);
	}

	public:
	
	Game * game;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;
	virtual void reset() { }

};

#endif
