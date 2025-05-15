#include <iostream>
#include <vector>
#include <string>
#include "location.hpp"
#include "graph.hpp"

using namespace std;

// constructor
Location::Location () {
        player_in = false;
        North = 0;
        South = 0;
        East = 0;
        West = 0;
}
Location::Location (vector<string> items_list, string description, int north, int south, int east, int west) {
    player_in = false;
    items = items_list;
    desc = description;
    North = north;
    South = south;
    East = east;
    West = west;
}

string Location::get_location () {
    return desc;
}

vector<string> Location::get_items () {
    return items;
}

string Location::remove_item (string to_remove) {
    int item_vector_length = items.size();
    int to_remove_length = to_remove.length();
    bool is_same = false;

    for (int a = 0; a < item_vector_length; a++) {
        string indiv_item = items[a];
        int indiv_item_length = indiv_item.length();
        for (int b = 0; b < indiv_item_length; b++) {
            if (indiv_item_length == to_remove_length) {
                if (tolower(indiv_item[b]) != tolower(to_remove[b])) {
                    is_same = false;
                }
                else {
                    is_same = true;
                }
            }
            else {
                is_same = false;
            }
        }
        if (is_same) {
            items.erase(items.begin() + a);
            return to_remove;
        }
    }

    return to_remove;
}

bool Location::is_player_in () {
    return player_in;
}

void Location::player_update (bool in_or_out) {
    player_in = in_or_out;
}

int Location::get_north () {
    return North;
}
int Location::get_south () {
    return South;
}
int Location::get_east (){
    return East;
}
int Location::get_west () {
    return West;
}

void Location::change_north (int val) {
    North = val;
}
void Location::change_south (int val) {
    South = val;
}
void Location::change_east (int val) {
    East = val;
}
void Location::change_west (int val) {
    West = val;
}