#ifndef UUID_97114E6B_44C3_40B0_BBA0_430260671E4C
#define UUID_97114E6B_44C3_40B0_BBA0_430260671E4C

#include <SFML/Graphics/Texture.hpp>
#include "game_state.hpp"

class GameStateMap : public GameState {
	private:
	sf::View view;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	// ..
	
	public:
	
	GameStateMap(Game * g) {
		game = g;
		texture.loadFromFile("europa.jpg");
		sprite.setTexture(texture);
		position = sprite.getPosition();
	}

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	
	void loadgame();

};

#endif
