#ifndef UUID_332834D9_E94F_44E9_8377_6A982899DD51
#define UUID_332834D9_E94F_44E9_8377_6A982899DD51

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <SFML/System/Vector2.hpp>

using namespace std;

class node;
class edge;

class edge {

	int id;

public:
	shared_ptr<node> from;
	shared_ptr<node> to;
	int get_id();
	shared_ptr<node> get_from();
	shared_ptr<node> get_to();
	edge(int id, shared_ptr<node> from, shared_ptr<node> to);
};


class node : public sf::Vector2f {

private: 
	int id;
	string name;
	vector<shared_ptr<edge>> connections;
	unordered_map<string, double> weights;

public:
	double get_weight(string key);
	void add_weight(string key, double value);

	int get_x();
	int get_y();
	string get_name();
	vector<shared_ptr<edge>> get_connections();

	node(int id, string name, int x, int y, vector<shared_ptr<edge>> connections);
};

#endif
