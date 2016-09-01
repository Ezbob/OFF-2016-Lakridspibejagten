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
	
	
	Sprite sprite;
	Texture texture;
	Vector2f position;

	animation * character;
	Texture character_texture;
	Text * t = new Text();

	static constexpr double delay = 0.5;
	float scale = 1.0;
	node_graph graph;
	map<string,Vector2f> positions;
	string current_node;
	string target_node;
	double route_position;
	vector<GameState*> mini_games;
	public:
	
	GameStateMap(Game * g, node_graph gr, map<string,Vector2f> ps, vector<GameState*> mg);
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void reset();
	void select_route();
	void loadgame();

};

#endif
