#ifndef C_GRAPH
#define C_GRAPH

#include <iostream>
#include <vector>
#include <string>

class Location;

using namespace std;

class Graph {

    private:
        // vector of every location
        vector<Location*> l_map;

    public:
        // constructor
        Graph (vector<Location*> locations);
        // moves player between locations, returns true if it worked false if it didn't
        bool move (int loc_index);

};

#endif