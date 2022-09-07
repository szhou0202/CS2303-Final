
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>

using namespace std;

#include "Hotel.h"

class Robot {
    public:
        // METHODS
        Robot();
        Robot(Hotel* h);
        void dfs(ofstream* fout, Hotel* hotel, int current_room, int* num_visits, 
        int* num_rooms_visited, bool* finished, stack<int>* to_visit, int* adj_mat);
        
        // INSTANCE VARS
        bool* finished;
        // Hotel* hotel;
};