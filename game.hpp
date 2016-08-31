#ifndef UUID_6D85E1C5_01DF_4D11_AB49_8F2D6603D018
#define UUID_6D85E1C5_01DF_4D11_AB49_8F2D6603D018

#include <SFML/Graphics.hpp>

class GameState;

class Game {
	public:

	sf::RenderWindow window;

	void gameloop();

	Game();
	~Game();
};

#endif
