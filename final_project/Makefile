CC = g++
CFLAGS = -Wall -std=c++14

game: game.o graph.o location.o
	$(CC) $(CFLAGS) game.o graph.o location.o -o game

graph_and_location_test: graph_and_location_test.o graph.o location.o
	$(CC) $(CFLAGS) graph_and_location_test.o graph.o location.o -o graph_and_location_test

game.o: game.cpp graph.hpp location.hpp
	$(CC) $(CFLAGS) -c game.cpp

graph_and_location_test.o: graph_and_location_test.cpp graph.hpp location.hpp
	$(CC) $(CFLAGS) -c graph_and_location_test.cpp

graph.o: graph.cpp graph.hpp
	$(CC) $(CFLAGS) -c graph.cpp

location.o: location.cpp location.hpp graph.hpp
	$(CC) $(CFLAGS) -c location.cpp

clean:
	rm *.o