#include <SFML/Graphics.hpp>

class GameState;

class Game {
	public:

	sf::RenderWindow window;

	void game_loop();

	Game();
	~Game();
};
