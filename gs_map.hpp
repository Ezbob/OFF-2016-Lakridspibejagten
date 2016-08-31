#ifndef UUID_97114E6B_44C3_40B0_BBA0_430260671E4C
#define UUID_97114E6B_44C3_40B0_BBA0_430260671E4C

#include <SFML/Graphics/Texture.hpp>
#include "game_state.hpp"

class GameStateMap : public GameState, public sf::Texture {
	private:
	
	unsigned x;
	unsigned y;
	sf::View view;
	
	// ..
	
	public:
	
	GameStateMap(Game * g, unsigned _x = 0, unsigned _y = 0) {
		game = g;
		x = _x;
		y = _y;
		loadFromFile("europa.jpg");
	}

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	virtual void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void loadgame();

};

#endif
