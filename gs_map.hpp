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
