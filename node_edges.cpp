#include "node_edges.hpp"

// edge

edge::edge(int id, shared_ptr<node> from, shared_ptr<node> to) {
	this->id = id;
	this->from = from;
	this->to = to;
}

int edge::get_id() {
	return this->id;
}

shared_ptr<node> edge::get_from() {
	return this->from; 
}

shared_ptr<node> edge::get_to() {
	return this->to;
}

// node

double node::get_weight(string key) {
	return this->weights[key];
}

void node::add_weight(string key, double value) {
	this->weights[key] = value;
}

int node::get_x() {
	return this->x;
}

int node::get_y() {
	return this->y;
}

string node::get_name() {
	return this->name;
}

vector<shared_ptr<edge>> node::get_connections() {
	return this->connections;
}

node::node(int id, string name, int x, int y, vector<shared_ptr<edge>> v) {
	this->id = id;
	this->x = x;
	this->y = y;
	this->connections = v;
}

