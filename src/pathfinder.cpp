#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file test_pairs_file output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];
  char* pairs_filename = argv[2];
  char* output_filename = argv[3];

  //TODO   
 /* You can call the pathfinder function from here */
  Graph graph;
  graph.loadFromFile(graph_filename);
  
  ifstream pairfile(pairs_filename);
  ofstream output;
  output.open(output_filename);
  while(pairfile){
	if(!pairfile.eof()) {
		string s;

        	if(!getline(pairfile, s)) {
			break;
		}
 
        	istringstream ss(s);	

        	vector<string> pairs;
		while(ss){
			string val;
                	if(!getline(ss, val, ' ')) break;
			pairs.push_back(val);
		}

		if(pairs.size() != 2){
			continue;
		}

		Node * start = new Node(pairs[0]);
  		Node * finish = new Node(pairs[1]);	
	  
		if(graph.pathfinder(start, finish)) {
			graph.printPath(start, finish, output);
		}else {
			output <<  "\n";
		}
	
        	delete start;
		delete finish;
	}else {
		break;
	}
  }
  return 1;
}  
