#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <time.h>


#include <SFML/System/Vector2.hpp>

#include "game.hpp"
#include "mock_gamestate.hpp"
#include "gs_map.hpp"
#include "mg_runner.hpp"
#include "gs_treeout.hpp"
#include "gs_description.hpp"

using namespace std;

int mainGame() {
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

	vector<GameState*> mini_games {
		new GameStateMockMiniGame(&game)
	};
	GameStateMap map(&game, graph, positions, mini_games);
	game.pushState(&map);

	game.gameloop();

	return 0;
}

int testMiniGame() {
	Game game;

	game.pushState(new GameStateDescription(&game, "Yaya"));
	game.pushState(new GameStateTreeout(&game));
	game.pushState(new GameStateMockMiniGame(&game));
	game.pushState(new GameStateDescription(&game, "Ja hallaa hvad klok er 'et?\n"));
	game.gameloop();

	return 0;
}

int main() {
	srand(time(NULL));

	//return mainGame();
	return testMiniGame();
}
