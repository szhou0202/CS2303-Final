
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "Hotel.h"
#include "Robot.h"

using namespace std;

int main(int argc, char* argv[]) {

    // 1) get the filenames 
    /*
    char* filename = new char[20];
    cout << "Please enter an input filename: " << endl;
    cin >> filename;
    char* ofilename = new char[20];
    cout << "Please enter an output filename: " << endl;
    cin >> ofilename;*/
    
    char* filename = argv[1];
    if(filename == NULL) {
        printf("No input filename given.\n");
        return 0;
    }
    char* out_filename = argv[2];
    if(out_filename == NULL) {
        printf("No output filename given.\n");
        return 0;
    }


    // 2) open file as ifstream
    ifstream fp; fp.open(filename);
    if(fp == NULL) {
        printf("This file does not exist.\n");
        return 0;
    }
    
    // a) declare and initialize our Hotel
    int num_rooms; fp >> num_rooms;
    Hotel* hotel = new Hotel(num_rooms);
    hotel->rooms = (Room*) malloc(num_rooms * sizeof(Room));
    
    // b) iterate through the file and declare and initialize rooms
    string delim = ",";
    for(int i = 0; i < num_rooms; i++) {

        // i) set room_num, num_neighbors, and neighbors
        (*(hotel->rooms + i)).room_num = i; 
        (*(hotel->rooms + i)).num_neighbors = 0; 
        vector<int> v; (*(hotel->rooms + i)).neighbors = v; 

        // ii) get new line
        string line;
        fp >> line;

        // iii) loop through, add to room's neighbors and increment room's num_neighbors
        int pos = 0;
        while(pos != string::npos) { 

            // !!! referenced this page: 
            // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
            
            pos = line.find(delim);
            int num = stoi(line.substr(0, pos));
            line.erase(0, pos + delim.length());

            (*(hotel->rooms + i)).num_neighbors += 1;
            (*(hotel->rooms + i)).neighbors.push_back(num);
        }
    }


    // 3) find a path through the hotel floor using DFS
    bool* visited = (bool*) malloc(num_rooms * sizeof(bool)); 
    int* num_visits = (int*) malloc(num_rooms * sizeof(int));
    ofstream* fout = new ofstream(); (*fout).open(out_filename);

    Robot* robot = new Robot();

    robot->finished = (bool*) malloc(sizeof(bool));
    bool* finished = (bool*) malloc(sizeof(bool));
    int* num_rooms_visited = (int*) malloc(sizeof(int));
    int* adj_mat = (int*) malloc(pow((hotel->num_rooms), 2) * sizeof(int));
    stack<int>* to_visit = (stack<int>*) malloc(sizeof(stack<int>));

    (*robot).dfs(fout, hotel, 0, num_visits, num_rooms_visited, finished, to_visit, adj_mat);

    fp.close();
    (*fout).close();
    free(hotel->rooms);
    free(hotel);
    
    return 0;
}
