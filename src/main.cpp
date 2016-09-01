#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <time.h>


#include <SFML/System/Vector2.hpp>

#include "game.hpp"
#include "states/mock_gamestate.hpp"
#include "states/gs_map.hpp"
#include "states/mg_runner.hpp"
#include "states/gs_treeout.hpp"
#include "states/gs_description.hpp"
#include "assets.hpp"

using namespace std;

GameState * new_game_state(Game * g) {
	static auto mini_game_count = 2;
	auto r = rand() % mini_game_count;
	switch(r) {
		case 0: return new MiniGameRunner(g); break;
		case 1: return new GameStateTreeout(g); break;
	}

	return 0;
}

int main() {
	/* Indlæs skriftyper */
	assets::font_main.loadFromFile("assets/main_font.ttf");
	assets::font_description.loadFromFile("assets/desc_font.ttf");
	/* Indlæs textures */
	assets::world.loadFromFile("assets/map.jpg");

	assets::background.loadFromFile("assets/tiling_background.png");
	assets::background.setRepeated(true);
	assets::background.setSmooth(true);

	assets::ball.loadFromFile("assets/ball.png");
	assets::runner.loadFromFile("assets/ani/run.png");
	assets::rock.loadFromFile("assets/imgs/rock1.png");
	assets::pibe.loadFromFile("assets/imgs/pibe.png");

	// Create game
	Game game;

	// indlæs knuder
	fstream arcs("arcs.txt");
	string from;
	string to;
	node_graph graph;
	float weight;

	while (arcs) {
		arcs >> from >> to >> weight;
		graph[from][to] = weight;
		graph[to][from] = weight;
	}

	// indlæs positioner 
	fstream nodes("nodes.txt");
	map<string, Vector2f> positions;
	string name;
	float x; float y;
	while (nodes) {
		nodes >> name >> x >> y;
		positions[name] = Vector2f(x,y);
	}

	map<string, GameState*> node_games;
	for (auto i : positions) node_games[i.first] = new_game_state(&game);


	assets::ball_sprite.setTexture(assets::ball);
	assets::runner_sprite.setTexture(assets::runner);
	assets::background_sprite.setTexture(assets::background);
	assets::world_sprite.setTexture(assets::world);
	assets::player_sprite.setTexture(assets::player_texture);
	assets::rock_sprite.setTexture(assets::rock);
	assets::pibe_sprite.setTexture(assets::pibe);
	assets::runner_animation = new animation({0,1,2,3,4,5}, assets::runner);

#if 1
	GameStateMap map(&game, graph, positions, node_games, "Odense", "Nyborg");

	game.pushState(new GameStateDescription(&game, "You're done"));
	game.pushState(&map);
#else
	//game.pushState(new GameStateDescription(&game, "Yala3\n"));
	game.pushState(new MiniGameRunner(&game));
	//game.pushState(new GameStateDescription(&game, "Yala2\n"));
	//game.pushState(new GameStateDescription(&game, "Yala\n"));
	//game.pushState(new GameStateTreeout(&game));
#endif
	game.gameloop();

	return 0;
}
