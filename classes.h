#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

int SCORE = 0;

bool check_valid_pos(vector<pair<int,int>>curr_coords);

int BOARD[BOARD_HEIGHT][BOARD_WIDTH] = {}; //[r][c]

struct block{

    vector<pair<int,int>>coords;
    int type = 0;

    void generate_piece(){
        int selection = rand()%7 + 1;
        switch(selection){
            case 1: //I BLOCK
                this->coords = {
                    {1,3},
                    {1,4},
                    {1,5},
                    {1,6}
                };
                this->type = 2;
                break;
            case 2: //J BLOCK
                this->coords = {
                    {1,5},
                    {2,5},
                    {3,4},
                    {3,5}
                };
                this->type = 3;
                break;
            case 3: //L BLOCK
                this->coords = {
                    {1,5},
                    {2,5},
                    {3,5},
                    {3,6}
                };
                this->type = 4;
                break;
            case 4: //Z BLOCK
                this->coords = {
                    {1,4},
                    {1,5},
                    {2,5},
                    {2,6}
                };
                this->type = 5;
                break;
            case 5: //S BLOCK
                this->coords = {
                    {1,5},
                    {1,6},
                    {2,4},
                    {2,5}
                };
                this->type = 6;
                break;
            case 6: //T BLOCK
                this->coords = {
                    {1,4},
                    {1,5},
                    {1,6},
                    {2,5}
                };
                this->type = 7;
                break;
            case 7: //O BLOCK
                this->coords = {
                    {1,4},
                    {1,5},
                    {2,4},
                    {2,5}
                };
                this->type = 8;
                break;
        }
    }
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
            coords = {new_coords};
        }
    }

};

bool check_valid_pos(vector<pair<int,int>>curr_coords){ //check if B is in valid position on board
    
    int row, col;

    for(pair<int,int>pos:curr_coords){
        row = pos.first;
        col = pos.second;
        if(row < 1 || row > BOARD_HEIGHT-2){
            return false;
        }
        if(col < 1 || col < BOARD_WIDTH-2){
            return false;
        }
        if(BOARD[row][col] != 0){
            return false;
        }
    }
   
    return true;

} 

#endif