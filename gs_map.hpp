#ifndef UUID_97114E6B_44C3_40B0_BBA0_430260671E4C
#define UUID_97114E6B_44C3_40B0_BBA0_430260671E4C

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class GameStateMap : public GameState {
	private:
	
	sf::View view;

	// ..
	
	public:
	
	GameStateMap(Game *game);
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	
	void loadgame();

};

#endif
