#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <fstream>

using namespace std;

string file_names[4] = {"hs_easy.txt", "hs_med.txt", "hs_hard.txt", "hs_impossible.txt"};

int read_score(int diff);
void write_score(int s, int diff);

int read_score(int diff){
    int score = 0;
    ifstream FILE;
    FILE.open(file_names[diff]);
    if(FILE){
        FILE>>score;
        FILE.close();
    }
    return score;
}

void write_score(int s, int diff){
    ofstream FILE;
    FILE.open(file_names[diff]);
    FILE<<s;
    FILE.close();
}

#endif