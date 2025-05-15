#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "graph.hpp"
#include "location.hpp"

using namespace std;

// exists to make it easier to print to the console and write to a file the same information 
string print (string text) {
    cout << text << endl;
    return text;
}

// prints player inventory
void get_inventory (vector<string> *inventory) {
    int length = inventory->size();
    if (length <= 0) {
        cout << "There is nothing in your inventory." << endl;
    }
    for (int i = 0; i < length; i++) {
        cout << (*inventory)[i] << endl;
    }
}

// returns the index of the player's location in the map
int player_loc (vector<Location*> theforest) {
    int length = theforest.size();
    for (int i = 0; i < length; i++) {
        if (theforest[i]->is_player_in()) {
            return i;
        }
    }
    return -1;
}

// removes an item from the location and adds it to the player's inventory
void take (string to_take, vector<Location*> theforest, vector<string> *inventory) {
    int p_l = player_loc(theforest);
    theforest[p_l]->remove_item(to_take);
    inventory->push_back(to_take);
}

// calls the move action to go the specified direction
void go (string direction, Graph *map, vector<Location*> theforest) {
    int l = player_loc(theforest);
    theforest[l]->player_update(false);

    if (direction == "north") {
        map->move(theforest[l]->get_north());
    }
    else if (direction == "south") {
        map->move(theforest[l]->get_south());
    }
    else if (direction == "east") {
        map->move(theforest[l]->get_east());
    }
    else {
        map->move(theforest[l]->get_west());
    }
}

// checks what the player entered and calls the associated functions
void read_action (string action, Graph *map, vector<Location*> theforest, vector<string> *inventory) {
    if (action == "help") {
        cout << "'north': move north, if possible\n'south': move south, if possible\n'east': move east, if possible\n'west': move west, if possible" << endl;
        cout << "'take [item]': add the specified item to your inventory. for example: 'take key'" << endl;
        cout << "'inventory': see the items in your inventory" << endl;
        return;
    }
    else if (action == "north" || action == "south" || action == "east" || action == "west") {
        go(action, map, theforest);
        return;
    }
    else if (action.find("take ") == 0) {
        action = action.substr(5);
        vector<string> items = theforest[player_loc(theforest)]->get_items();
        int c = count(items.begin(), items.end(), action);
        if (c > 0) {
            take(action, theforest, inventory);
        }
        else {
            cout << "Could not find that item." << endl;
        }
        return;
    }
    else if (action == "inventory") {
        get_inventory(inventory);
        return;
    }
    else {
        print("Action not recognized.");
    }
}

int main(int argc, char * argv[]) {
    // read file from command line (adventure.txt is provided but any .txt file should work)
    if (argc < 2) {
        cout << "No filename specified" << endl;
        exit(1);
    }

    string filename = argv[1];

    // location and graph setup
    Location clearing0({"twigs", "berries"}, "You are in a small clearing in the middle of the forest. To the north is a path. In all other directions there is nothing but trees.", 3, 0, 0, 0);
    Location lakeside1({"driftwood", "fishing line"}, "You are at the shore of a large lake. To the west is a path. To the north and south, the lakeshore continues indefinitely. To the east is nothing but water.", 1, 1, 1, 3);
    Location cliff2({"rocks"}, "You are at the bottom of a tall cliff. To the east is a small path. To the west, there is something buried in the undergrowth. To the north is the sheer cliff face. To the south is nothing but trees.", 2, 2, 4, 5);
    Location forest3({}, "You are on a forked path in the forest. To the south is a clearing. To the west the path leads deeper into the forest. The path continues north. To the east the trees start to thin.", 4, 0, 1, 6);
    Location cabin4({}, "You are outside a small cabin in the middle of the forest. To the south is a path. To the west is a smaller, less traveled path. To the north and south there is nothing but trees.", 4, 3, 4, 2);
    Location ruin5({"boards"}, "You are near an abandoned shack being swallowed by the forest. To the east is a cliff. To the south is a path of fragmented old train tracks. In all other directions there is nothing but trees.", 5, 6, 2, 5);
    Location railroad6({"spikes"}, "You are on a set of old train tracks that are pulled up or missing in several places. To the north there is something buried in the undergrowth. To the east is a path. To the west you can hear running water. To the south is nothing but trees.", 5, 6, 3, 7);
    Location riverbank7({"stones", "bones"}, "You are on the bank of a small river. To the east the forest undergrowth is a little thinner. To the south, you can walk along the river bank. To the north you could walk along the river bank if not for the large alligator lounging there that you do not want to walk past. To the west is the other side of the river, which you cannot cross.", 7, 8, 6, 7);
    Location road8({}, "You are on a gravel road. Luckily, you recognize it. To the south is your home.", 8, 9, 8, 8);
    Location home9;

    vector<Location*> theforest = {&clearing0, &lakeside1, &cliff2, &forest3, &cabin4, &ruin5, &railroad6, &riverbank7, &road8, &home9};
    Graph map(theforest);

    clearing0.player_update(true);

    // keep track of where the player is
    int plyr_l = player_loc(theforest);

    // tracks if end condition is met
    bool win = false;

    // player inventory
    vector<string> inventory;

    // writing to file
    ofstream output;
    output.open(filename);

    // checks if file open failed
    if (output.fail()) {
        cout << "Cannot open: " << filename << endl;
        exit(1); 
    }

    // game starts here!
    output << print("You are lost in the forest. You should probably try to find your way out.\n") << endl;
    do {
        // print the current location's description
        output << print(theforest[plyr_l]->get_location()) << endl;
        // print the items in the current location
        vector<string> items = theforest[plyr_l]->get_items();
        int i_length = items.size();
        if (i_length > 0) {
            output << print("Looking around, you see some: ") << endl;
            for (int i = 0; i < i_length; i++) {
                output << print(items[i]) << endl;
            }
        }
        cout << "(Type 'help' for a list of actions.)" << endl;

        // take player input
        string input = "";
	    getline(cin, input);

        read_action(input, &map, theforest, &inventory);
        // update plyr_l if necessary
        plyr_l = player_loc(theforest);

        // write which way you went to the file (since i'm not writing your input directly, this'll make the file look nicer)
        if (input == "north" || input == "south" || input == "east" || input == "west") {
            output << "You decide to go " << input << "." << endl;
        }
        // write item you took to the file
        else if (input.find("take ") == 0) {
            string thing = input.substr(5);
            if (count(items.begin(), items.end(), thing) > 0) {
                output << "You decide to take some " << thing << "." << endl;
            }
        }

        // win condition
        if (home9.is_player_in()) {
            win = true;
        }

    }while(!win);

    output << print("Congratulations! You found your way out of the forest!") << endl;

    int inv_siz = inventory.size();
    if (inv_siz > 0) {
        output << print("You also found some souvenirs along the way: ") << endl;
        for (int s = 0; s < inv_siz; s++) {
            output << print(inventory[s]) << endl;
        }
    }

    output.close();

    return 0;
}