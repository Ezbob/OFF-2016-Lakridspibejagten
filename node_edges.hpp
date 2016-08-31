#ifndef UUID_332834D9_E94F_44E9_8377_6A982899DD51
#define UUID_332834D9_E94F_44E9_8377_6A982899DD51

#include <vector>
#include <string>
#include <map>
#include <memory>

using namespace std;

class node;
class edge;

class edge {

private:
	int id;
	shared_ptr<node> from;
	shared_ptr<node> to;

public:
	edge(int id, node *from, node *to);
	~edge();
};


class node {

private: 
	int id;
	int x, y;
	string name;
	vector<edge> connections;
	map<string, double> weights;

public:
	double get_weight(string key);
	void add_weight(string key, double value);

	node(int id, int x, int y, vector<edge> connections);
	~node();
};

#endif
