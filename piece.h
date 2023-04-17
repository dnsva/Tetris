
#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>
#include <utility>

#include "board.h"

using namespace std;

struct block{

    vector<pair<int,int>>coords;
    int type = 0;

    void generate_piece();
    void rotatePiece(){
        vector<pair<int,int>>new_coords(coords);

        int cx = (new_coords[0].first + new_coords[1].first + new_coords[2].first + new_coords[3].first) / 4;
        int cy = (new_coords[0].second + new_coords[1].second + new_coords[2].second + new_coords[3].second) / 4;

        // Rotate each point of the block around the center
        for (int i = 0; i < 4; i++) {
            int tmp_x = new_coords[i].first;
            int tmp_y = new_coords[i].second;
            new_coords[i].first = cx + (tmp_y - cy);
            new_coords[i].second = cy - (tmp_x - cx);
        }

        //check if valid
        if(check_valid_pos(new_coords)){
            block.coords = new_coords;
        }
    }

};


block I_BLOCK, J_BLOCK, L_BLOCK, Z_BLOCK, S_BLOCK, T_BLOCK, O_BLOCK;

I_BLOCK.coords = {
    {1,3},
    {1,4},
    {1,5},
    {1,6}
}

J_BLOCK.coords = {
    {1,5},
    {2,5},
    {3,4},
    {3,5}
}

L_BLOCK.coords = {
    {1,5},
    {2,5},
    {3,5},
    {3,6}
}

Z_BLOCK.coords = {
    {1,4},
    {1,5},
    {2,5},
    {2,6}
}

S_BLOCK.coords = {
    {1,5},
    {1,6},
    {2,4},
    {2,5}
}

T_BLOCK.coords = {
    {1,4},
    {1,5},
    {1,6},
    {2,5}
}

O_BLOCK.coords = {
    {1,4},
    {1,5},
    {2,4},
    {2,5}
}

I_BLOCK.type = 2;
J_BLOCK.type = 3;
L_BLOCK.type = 4;
Z_BLOCK.type = 5;
S_BLOCK.type = 6;
T_BLOCK.type = 7;
O_BLOCK.type = 8;

block::generate_piece(){

    int selection = rand()%7 + 1;
    switch(selection){
        case 1:
            this->coords = I_BLOCK.coords;
            this->type = I_BLOCK.type;
            break;
        case 2:
            this->coords = J_BLOCK.coords;
            this->type = J_BLOCK.type;
            break;
        case 3:
            this->coords = L_BLOCK.coords;
            this->type = L_BLOCK.type;
            break;
        case 4:
            this->coords = Z_BLOCK.coords;
            this->type = Z_BLOCK.type;
            break;
        case 5:
            this->coords = S_BLOCK.coords;
            this->type = S_BLOCK.type;
            break;
        case 6:
            this->coords = T_BLOCK.coords;
            this->type = T_BLOCK.type;
            break;
        case 7:
            this->coords = 0_BLOCK.coords;
            this->type = 0_BLOCK.type;
            break;
    }

}

#endif