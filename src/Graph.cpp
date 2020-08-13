#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <iterator>
#include <stack>
#include <queue> 

using namespace std;

Graph::Graph(void)
    : users(0) {}

Graph::~Graph(void) {
  for(auto itr : users) {
	delete itr.second;
  }
}

/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */
//TODO

 
/* Read in relationships from an inputfile to create a graph */

bool Graph::loadFromFile(const char* in_filename) {
  ifstream infile(in_filename);

  while (infile) {
    string s;
    if (!getline(infile, s)) break;

    istringstream ss(s);
    vector<string> record;

    while (ss) {
      string s;
      if (!getline(ss, s, ' ')) break;
      record.push_back(s);
    }

    if (record.size() != 2) {
      continue;
    }

    //TODO - YOU HAVE THE PAIR OF IDS OF 2 FRIENDS IN 'RECORD'. WHAT DO NEED TO DO NOW?
      
    // check to see if hashmap already has the key
    auto search_one = users.find(record[0]);
    auto search_two = users.find(record[1]);
    Node * temp1 = nullptr;
    Node * temp2 = nullptr;
    if(search_one == users.end()) {
	  Node* nodeOne = new Node(record[0]);
	  users.insert({nodeOne->data, nodeOne});
	  temp1 = nodeOne;
    }
    if(search_two == users.end()){
	  Node* nodeTwo = new Node(record[1]);
	  users.insert({nodeTwo->data, nodeTwo});
	  temp2 = nodeTwo;
    }
    if(temp1 == nullptr){
	temp1 = search_one->second;
    }
    if(temp2 == nullptr){
	temp2 = search_two->second;
    }

    if(std::find(temp1->friends.begin(),temp1->friends.end(),temp2) == temp1->friends.end()){
     	  temp1->friends.push_back(temp2);
    }
    if(std::find(temp2->friends.begin(),temp2->friends.end(),temp1) == temp2->friends.end()){
     	  temp2->friends.push_back(temp1);
    }

  } 
  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

/* Implement pathfinder*/
//TODO 
bool Graph::pathfinder(Node* from, Node* to) {
    auto itr = users.begin();
    while(itr != users.end()) {
       itr->second->visited = false;
       itr->second->prev = nullptr;
       itr++;	
    } 

    std::queue<Node*> que;
    Node * curr;
    // Do we need to find this?
    auto search_from = users.find(from->data);
    auto search_to = users.find(to->data);
    if(search_from != users.end() && search_to != users.end()) {
        //found
         search_from->second->visited = true;
        que.push(search_from->second);
        while(!que.empty()) {
            curr = que.front();
	    que.pop();
	    if(curr->data == to->data) {
		return true;
            }
            for(int i = 0; i < (curr->friends).size();i++) {
                if(!curr->friends[i]->visited) {
		    curr->friends[i]->visited = true;
                    curr->friends[i]->prev = curr;
                    que.push(curr->friends[i]);
                }else {
                    // do nothing
                }
            }
        }
    }
	// keys dont exist, how to handle?
        return false;
}

/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<string>& invitees, const int& k) {
	auto search = users.begin();
	std::priority_queue<std::pair<int, Node *>> pqueue;
	while(search != users.end()) {
		search->second->visited = false;
		search->second->degree = search->second->friends.size();
		pqueue.push(make_pair(search->second->degree,search->second));
		search++;
	}
	while(!pqueue.empty()){
		Node * curr = pqueue.top().second;
		pqueue.pop();
		if(!curr->visited && curr->degree < k){
			curr->visited = true;
			for(int i = 0; i < curr->friends.size(); i++){
				curr->friends[i]->degree--;
				if(curr->friends[i]->degree < k){
					curr->friends[i]->visited == false;
					pqueue.push(make_pair(curr->friends[i]->degree, curr->friends[i]));
				}
			}
		}	
	}		
	auto search2 = users.begin();
	while(search2 != users.end()){
		if(search2->second->degree >= k){
			invitees.push_back(search2->second->data);
		}
	search2++;
	}
}

/*
 * Helper to print path solution
 */
void Graph::printPath(Node* from, Node* to, ostream& output) {
    vector<string> path;
    auto search = users.find(to->data);
    if(search != users.end()){
	Node* curr = search->second;

   	 while(curr->data != from->data) {
        	path.push_back(curr->data);
        	curr = curr->prev;
    	}
    }
    //write to outfile
    output << from->data;
    for(int i=path.size()-1; i>=0; --i) {
        output << " " << path[i];
    }
    output << endl;
}

/*
 * Helper to print path solution for social gathering
 */
void Graph::printGathering(vector<string> kInvites, ostream& output) {
	int convert;
	vector<int> myInvites;

        for(int i=0; i<kInvites.size(); i++) {
		convert = stoi(kInvites[i]);
		myInvites.push_back(convert);
	}

	std::sort(myInvites.begin(), myInvites.end());
        output << myInvites[0];
	for(int i=1; i<myInvites.size(); i++) {
		output << endl << myInvites[i];
	}
}
