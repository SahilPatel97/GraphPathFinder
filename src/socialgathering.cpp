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
       << " friendship_pairs_file k_value output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    usage(argv[0]);
  }
  char* graph_filename = argv[1];
  char* output_filename = argv[3];
  istringstream ss(argv[2]);

 //TODO
 /* You can call the social gathering function from here */
 Graph graph;
 graph.loadFromFile(graph_filename);
 ofstream output;
 output.open(output_filename);
 string str;
 int k;
 ss >> str;
 k = std::stoi(str);
  
 vector<string> invites;

 graph.socialgathering(invites, k);
 graph.printGathering(invites, output);
 return 1; 
}
