#ifndef SCORE_H //guard
#define SCORE_H //guard

#include <string.h> //strings
#include <fstream> //files

using namespace std; //less typing 

string file_names[4] = {"hs_easy.txt", "hs_med.txt", "hs_hard.txt", "hs_impossible.txt"}; //file names 

int read_score(int diff); //fn 1
void write_score(int s, int diff); //fn2

int read_score(int diff){ //to get the score
    int score = 0; //default
    ifstream FILE; //make file var
    FILE.open(file_names[diff]); //open it
    if(FILE){ //if the descriptor exists
        FILE>>score; //cin the score
        FILE.close(); //close the file
    }
    return score; //return score value 
}

void write_score(int s, int diff){ //to rewrite it 
    ofstream FILE; //make file var
    FILE.open(file_names[diff]); //open it
    FILE<<s; //write
    FILE.close(); //close the file 
}

#endif //header guard