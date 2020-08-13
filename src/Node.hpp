#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
	string const data; //stores the data
    	int degree;
    	Node* prev; //previous node
    	bool visited;
	vector<Node*> friends; //vector holding address of all friends
	vector<string> edges; //vector holding the weights of the edges
	int degrees;	

	Node(const string &d) : data(d) {
        visited = false;
        prev = nullptr;
	}
	
};
#endif
