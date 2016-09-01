#ifndef UUID_97114E6B_44C3_40B0_BBA0_430260671E4C
#define UUID_97114E6B_44C3_40B0_BBA0_430260671E4C

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <map>
#include <string>
#include "animation.hpp"
#include "game_state.hpp"

using namespace std;
using namespace sf;

typedef map<string, map<string, float>> node_graph;

 
class GameStateMap : public GameState {
	private:
	Vector2f position;
	Text * t = new Text();

	static constexpr double delay = 0.5;
	node_graph graph;
	map<string,Vector2f> positions;
	string current_node;
	string target_node;
	string end_node;
	double route_position;
	map<string, GameState*> mini_games;
	public:
	
	GameStateMap(Game * g, node_graph gr, map<string,Vector2f> ps, map<string, GameState*> mg, string start, string target);
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void reset();
	void select_route();
	void loadgame();

};

#endif
