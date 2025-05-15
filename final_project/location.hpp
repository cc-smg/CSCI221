#ifndef LOC
#define LOC

#include <iostream>
#include <vector>
#include <string>

class Graph;

using namespace std;

class Location {
    private:
        // items in the location
        vector<string> items;
        // keeps track of if the player is in the location or not
        bool player_in;
        // description of the location
        string desc;
        // indexes of other locations in Graph's map vector
        int North;
        int South;
        int East;
        int West;
    public:
        // constructor
        Location ();
        Location (vector<string> items, string description, int north, int south, int east, int west);
        // gives description of the location
        string get_location ();
        // gives items in the location
        vector<string> get_items ();
        // removes an item from the items vector
        string remove_item (string to_remove);
        // gives the value of player_in 
        bool is_player_in ();
        // changes the value of player_in
        void player_update (bool in_or_out);
        // gives North South East or West
        int get_north ();
        int get_south ();
        int get_east ();
        int get_west ();
        // changes North South East or West and therefore where moving that direction leads
        void change_north (int val);
        void change_south (int val);
        void change_east (int val);
        void change_west (int val);

};

#endif