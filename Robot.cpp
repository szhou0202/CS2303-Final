
#include "Robot.h"

Robot::Robot() {
}

// dfs algo
// this is an optimization/change of dfs:
// we are keeping track of how many times 
// we visited an edge to not run into infinite loops
void Robot::dfs(ofstream* fout, Hotel* hotel, int current_room, int* num_visits, 
int* num_rooms_visited, bool* finished, stack<int>* to_visit, int* adj_mat) {
    while((*num_rooms_visited) == 0 || (*to_visit).size() > 0) {
        // 1) print that we are visiting this room
        (*fout) << "Visited room " << current_room << endl;

        // 2) check if this room has been visited before
        // if not, we will vaccuum it
        if((*(num_visits + current_room))==0) {
            (*fout) << "Vaccuumed room " << current_room << endl;
            *num_rooms_visited += 1;

            // a) increment num_visits for this room
            (*(num_visits + current_room)) += 1;

            // b) check if we're done vaccuuming
            if(*num_rooms_visited==hotel->num_rooms) {
                (*fout) << "Finished vaccuuming." << endl;
                (*(*this).finished) = *finished;
                *finished = true;
                return;
            };
        }
        else {
            (*(num_visits + current_room)) += 1;
        }

        // 3) add rooms to stack and continue
        for(int i = 0; i < (*(hotel->rooms + current_room)).num_neighbors; i++) { 
            int n = (*(hotel->rooms + current_room)).neighbors.at(i);
            if((*(adj_mat + current_room*(hotel->num_rooms) + n))<2) {
                (*to_visit).push(n);
            }
        }

        // a) track that we've traversed the edge between this and the next room
        int n = (*to_visit).top(); (*to_visit).pop();
        (*(adj_mat + current_room*(hotel->num_rooms) + n)) += 1;
        (*(adj_mat + n*(hotel->num_rooms) + current_room)) += 1;
        current_room=n;
    }
}
