#include <iostream>
#include <vector>
#include <string>
#include "graph.hpp"
#include "location.hpp"

using namespace std;

Graph::Graph (vector<Location*> locations) {
    l_map = locations;
}

bool Graph::move (int loc_index) {
    int length = l_map.size();

    if (loc_index >= length || loc_index < 0) {
        return false;
    }
    
    l_map[loc_index]->player_update(true);
    return true;
}