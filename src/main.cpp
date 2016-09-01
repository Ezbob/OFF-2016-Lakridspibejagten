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

int main() {
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

#if 0
	GameStateMap map(&game, graph, positions, 
		{
			new GameStateTreeout(&game),
			new MiniGameRunner(&game)
		}
	);

	game.pushState(new GameStateDescription(&game, "You're done"));
	game.pushState(&map);
#else
	game.pushState(new GameStateDescription(&game, "Yala3\n"));
	game.pushState(new MiniGameRunner(&game));
	game.pushState(new GameStateDescription(&game, "Yala2\n"));
	game.pushState(new GameStateDescription(&game, "Yala\n"));
	game.pushState(new GameStateTreeout(&game));
#endif
	game.gameloop();

	return 0;
}
