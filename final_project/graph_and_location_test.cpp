// testing for the graph and location classes
#include <iostream>
#include <vector>
#include <string>
#include "graph.hpp"
#include "location.hpp"

using namespace std;

// prints the items returned from get_items
void print_items (vector<string> items) {
    int length = items.size();
    for (int i = 0; i < length; i++) {
        cout << items[i] << endl;
    }
}

int main() {
    // basic functionality testing
    Location a;
    Location b({"cool item", "another item"}, "cool description", 2, 0, 0, 0);
    Location c;
    vector<Location*> locs = {&a, &b, &c};
    Graph g(locs);
    // test of player_update
    b.player_update(true);
    cout << "test of player_update and is_player_in, should be 1: " << b.is_player_in() << endl;
    // test of get_location
    cout << "test of get_location: " << b.get_location() << endl;
    cout << "test of get_location when no description was given: " << a.get_location() << endl;
    // test of get_items
    print_items(b.get_items());
    // test of get_items when no items were given
    print_items(a.get_items());
    // test of remove_item
    string removeditem = b.remove_item("another item");
    cout << "removed item: " << removeditem << endl;
    print_items(b.get_items());
    // test of get_(direction) functions
    cout << "North: " << b.get_north() << " South: " << b.get_south() << " East: " << b.get_east() << " West: " << b.get_west() << endl;
    // test of change_direction functions
    b.change_north(0);
    b.change_south(2);
    b.change_east(1);
    b.change_west(1);
    cout << "North: " << b.get_north() << " South: " << b.get_south() << " East: " << b.get_east() << " West: " << b.get_west() << endl;
    // test of move
    b.player_update(false);
    cout << "test of move, should return 1: " << g.move(b.get_north()) << endl;
    cout << "test of move changing player_in properly, should be 1: " << a.is_player_in() << endl;

    // more thorough testing
    cout << "--------------------------" << endl;
    // these should all branch off from woods in their respective directions and go only back to woods
    Location woods({"A Tree", "Berries", "Twigs"}, "it's the woods.", 1, 2, 3, 4);
    Location northwoods({"Things", "Stuff"}, "woods but north.", 1, 0, 1, 1);
    Location southwoods({"campfire", "grass"}, "woods but south", 0, 2, 2, 2);
    Location eastwoods({"Nothing Here"}, "woods but east", 3, 3, 3, 0);
    Location westwoods({"cabin", "a key", "bones"}, "woods but west", 4, 4, 0, 4);

    vector<Location*> woodslocs = {&woods, &northwoods, &southwoods, &eastwoods, &westwoods};
    Graph thewoods(woodslocs);
    
    woods.player_update(true);
    cout << woods.get_location() << endl;
    print_items(woods.get_items());

    cout << "going north now." << endl;
    woods.player_update(false);
    thewoods.move(woods.get_north());
    cout << northwoods.get_location() << endl;
    // trying to go north again, should still be in northwoods (should print 01000)
    thewoods.move(northwoods.get_north());
    print_items(northwoods.get_items());
    cout << woods.is_player_in() << northwoods.is_player_in() << southwoods.is_player_in() << eastwoods.is_player_in() << westwoods.is_player_in() << endl;
    // should be back in woods (print 1)
    northwoods.player_update(false);
    thewoods.move(northwoods.get_south());
    cout << woods.is_player_in() << endl;

    // try to go somewhere not in the graph
    thewoods.move(5);
    thewoods.move(-1);
    // should print 10000
    cout << woods.is_player_in() << northwoods.is_player_in() << southwoods.is_player_in() << eastwoods.is_player_in() << westwoods.is_player_in() << endl;
    
    cout << "removing Berries from woods" << endl;
    string removed = woods.remove_item("berries");
    print_items(woods.get_items());
    cout << "the removed item was: " << removed << endl;

    // try to remove an item that isn't there
    woods.remove_item("shark");
    print_items(woods.get_items());

    // change so that east from woods leads to westwoods, then try to go east
    woods.change_east(4);
    woods.player_update(false);
    thewoods.move(woods.get_east());
    cout << eastwoods.is_player_in() << endl;
    cout << westwoods.is_player_in() << endl;
    westwoods.player_update(false);
    thewoods.move(westwoods.get_east());

    // try changing north to a value that does not correspond to an index in thewoods and then moving there
    woods.change_north(7);
    thewoods.move(woods.get_north());
    return 0;
}