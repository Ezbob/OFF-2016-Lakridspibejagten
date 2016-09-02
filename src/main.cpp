#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <time.h>


#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>

#include "game.hpp"
#include "states/mock_gamestate.hpp"
#include "states/gs_map.hpp"
#include "states/mg_runner.hpp"
#include "states/end_state.hpp"
#include "states/gs_treeout.hpp"
#include "states/gs_description.hpp"
#include "assets.hpp"
#include "tetris.hpp"
#include "states/gs_splash.hpp"

using namespace std;

GameState * new_game_state(Game * g, int r) {
	/*
	static auto mini_game_count = 2;
	r = rand();	
	switch(r % mini_game_count) {
		case 0: return new MiniGameRunner(g); break;
		case 1: return new GameStateTreeout(g); break;
	}
	*/
	switch (r) {
		case 2: return new GameStateTreeout(g);
		case 4:	return new MiniGameRunner(g);
		//case 1: return new GameStateMockMiniGame(g);
		case 1: return new GameStateTetris(g); //GameStateMockMiniGame(g);//GameStateDescription(g, "Lorem ipsum");
		case 3: return new end_state(g);
		default:return NULL;
	}
}

int main() {
	/* Indlæs skriftyper */
	string first = "";
	string end = "";
	
	assets::font_main.loadFromFile("assets/main_font.ttf");
	assets::font_description.loadFromFile("assets/desc_font.ttf");
	/* Indlæs textures */
	assets::world.loadFromFile("assets/imgs/island.png");

// backgrounds
	assets::back_sky.loadFromFile("assets/imgs/back_sky.png");
	assets::back_sky.setRepeated(true);
	assets::back_sky.setSmooth(true);
	assets::back_mountains.loadFromFile("assets/imgs/back_mountains.png");
	assets::back_mountains.setRepeated(true);
	assets::back_mountains.setSmooth(true);
	assets::back_trees.loadFromFile("assets/imgs/back_trees.png");
	assets::back_trees.setRepeated(true);
	assets::back_trees.setSmooth(true);
	assets::back_grass.loadFromFile("assets/imgs/back_grass.png");
	assets::back_grass.setRepeated(true);
	assets::back_grass.setSmooth(true);
	assets::ball.loadFromFile("assets/ball.png");
	assets::runner.loadFromFile("assets/ani/run_jump.png");
	assets::catcher.loadFromFile("assets/ani/catch.png");
	assets::rock.loadFromFile("assets/imgs/rock1.png");
	assets::pibe.loadFromFile("assets/imgs/pibe.png");
	assets::gave.loadFromFile("assets/imgs/gave.png");
	assets::background_texture_treeout.loadFromFile("assets/imgs/gallery.png");
	assets::story_start.loadFromFile("assets/imgs/story_start.png");
	assets::story_win.loadFromFile("assets/imgs/story_win.png");
	assets::story_lose.loadFromFile("assets/imgs/rainyday.png");
	assets::basket.loadFromFile("assets/imgs/basket.png");
	assets::splash.loadFromFile("assets/imgs/splash.png");


	assets::ball_sprite.setTexture(assets::ball);
	assets::catcher_sprite.setTexture(assets::catcher);
	assets::runner_sprite.setTexture(assets::runner);
	assets::world_sprite.setTexture(assets::world);
	assets::player_sprite.setTexture(assets::player_texture);
	assets::rock_sprite.setTexture(assets::rock);
	assets::pibe_sprite.setTexture(assets::pibe);
	assets::gave_sprite.setTexture(assets::gave);
	assets::basket_sprite.setTexture(assets::basket);
	assets::background_sprite_treeout.setTexture(assets::background_texture_treeout);
	assets::runner_animation = new animation({0,1,2,3,4,5}, assets::runner, 48);
	assets::catcher_animation = new animation({0,1,2,3,4,5}, assets::catcher);

	// Create game
	Game game;

	// Create music
	sf::Music music;
	// Open it from an audio file
	if (music.openFromFile("assets/musik.wav")) {
		music.setLoop(true);
		music.play();
	}

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
	while (nodes) {
		string name;
		float x; float y;
		nodes >> name >> x >> y;
		if (name != "") end = name;
		if (first == "") first = name;
		positions[name] = Vector2f(x,y);
		std::cerr << first << " " << end << "\n";
	}

	int count = 0;

	//std::cerr << first << " " << end << "\n";
	map<string, GameState*> node_games;
	//for (auto i : positions) node_games[i.first] = new_game_state(&game, positions[i.first].x + positions[i.first].y);
	for (auto i : positions) {
		node_games[i.first] = new_game_state(&game, count++);//positions[i.first].x + positions[i.first].y);
	}

#if 1
	GameStateMap map(&game, graph, positions, node_games, first, end);
	game.pushState(&map);
	game.pushState(new GameStateDescription(&game));
	game.pushState(new GameStateSplash(&game));
#else
	// DEBUG
	//game.pushState(new GameStateDescription(&game, "Yala3\n"));
	//game.pushState(new MiniGameRunner(&game));
	//game.pushState(new GameStateDescription(&game, "Yala2\n"));
	//game.pushState(new GameStateDescription(&game, "Yala\n"));
	//game.pushState(new GameStateTreeout(&game));
	game.pushState(new end_state(&game));
#endif
	game.gameloop();

	return 0;
}
