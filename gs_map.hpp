#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class GameStateMap : public GameState {
	private:
	
	sf::View view;

	// ..
	
	public:
	
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateMap(Game *game);
};
