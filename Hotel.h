
#ifndef HOTEL_H_
#define HOTEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

// Room: represents a room
typedef struct Room {
    std::vector<int> neighbors;
    int num_neighbors;
    int room_num;
} Room;

// Hotel class
// (this is a bit unnecessary, really only stores a num_rooms for us)
class Hotel {
    public:
        // METHODS
        Hotel(int num_rooms); // constructor
        // Hotel(ifstream* inFile, char* filename);

        // INSTANCE VARS
        int num_rooms;
        struct Room* rooms; // an array of Rooms
        ifstream* inFile;
};

#endif
