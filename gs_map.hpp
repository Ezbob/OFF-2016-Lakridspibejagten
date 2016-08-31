#ifndef UUID_97114E6B_44C3_40B0_BBA0_430260671E4C
#define UUID_97114E6B_44C3_40B0_BBA0_430260671E4C

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <map>
#include <string>

#include "game_state.hpp"

using namespace std;
using namespace sf;

typedef map<string, map<string, float>> node_graph;

 
class GameStateMap : public GameState {

	private:
	sf::View view;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	float scale = 1.0;
	node_graph graph;
	map<string,Vector2f> positions;
	string current_node;
	Font node_font;

	public:
	
	GameStateMap(Game * g, node_graph gr, map<string,Vector2f> ps) {
		game = g;
		graph = gr;
		positions = ps;
		texture.loadFromFile("europa.jpg");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		position = sprite.getPosition();
		node_font.loadFromFile("/usr/share/wine/fonts/arial.ttf");
	}

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	void loadgame();

};

#endif
