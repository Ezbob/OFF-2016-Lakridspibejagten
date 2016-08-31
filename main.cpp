#include "game.hpp"
#include "gs_map.hpp"

int main() {
	Game game;

	game.pushState(new GameStateMap(&game));
	game.gameloop();

	return 0;
}
