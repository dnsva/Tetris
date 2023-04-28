#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int BOARD_WIDTH = 10;
int BOARD_HEIGHT = 20;

int DIFFICULTY = 0; //0 - easy, 1 - med, 2 - hard, 3 - impossible

int SCORE = 0;

bool check_valid_pos(vector<pair<int,int>>curr_coords);
void update_block_pos(vector<pair<int,int>>coords, int type);

int BOARD[100][100] = {}; //[r][c]

struct block{

    vector<pair<int,int>>coords;
    int type = 0;

    void generate_block(){
        int c = BOARD_WIDTH/2; //col num (will store center)
        int selection = rand()%7 + 1;
        switch(selection){
            case 1: //I BLOCK
                this->coords = {
                    {1,c-2},
                    {1,c-1},
                    {1,c},
                    {1,c+1}
                };
                this->type = 2;
                break;
            case 2: //J BLOCK
                this->coords = {
                    {1,c},
                    {2,c},
                    {3,c-1},
                    {3,c}
                };
                this->type = 3;
                break;
            case 3: //L BLOCK
                this->coords = {
                    {1,c},
                    {2,c},
                    {3,c},
                    {3,c+1}
                };
                this->type = 4;
                break;
            case 4: //Z BLOCK
                this->coords = {
                    {1,c-1},
                    {1,c},
                    {2,c},
                    {2,c+1}
                };
                this->type = 5;
                break;
            case 5: //S BLOCK
                this->coords = {
                    {1,c},
                    {1,c+1},
                    {2,c-1},
                    {2,c}
                };
                this->type = 6;
                break;
            case 6: //T BLOCK
                this->coords = {
                    {1,c-1},
                    {1,c},
                    {1,c+1},
                    {2,c}
                };
                this->type = 7;
                break;
            case 7: //O BLOCK
                this->coords = {
                    {1,c-1},
                    {1,c},
                    {2,c-1},
                    {2,c}
                };
                this->type = 8;
                break;
        }
    }
    void rotate_block(){
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
            update_block_pos(coords, type);
        }
    }
    bool check_collision(){
       //check if it has collided with the board
       for(pair<int,int>p:coords){
        if(BOARD[p.first+1][p.second] == 1){
            this->type = 1;
            return true;
        }
       }
       return false; //otherwise if no collision
    }

    void move_DOWN(){
        vector<pair<int,int>>new_coords(coords);

        for(int i = 0; i<new_coords.size(); ++i){
            new_coords[i].first++;
        }
        
        if(check_valid_pos(new_coords)){
            coords = {new_coords};
            update_block_pos(coords, type);
        }
    }
    void move_LEFT(){
        vector<pair<int,int>>new_coords(coords);

        for(int i = 0; i<new_coords.size(); ++i){

          //  printw("hello??\n");
            new_coords[i].second--;
        }
        
        //printw("CHECK VALID IS, %d", check_valid_pos(new_coords));
        if(check_valid_pos(new_coords)){
            coords = {new_coords};
            update_block_pos(coords, type);
        }
    }
    void move_RIGHT(){
        vector<pair<int,int>>new_coords(coords);

        for(int i = 0; i<new_coords.size(); ++i){
            new_coords[i].second++;
        }
        
        if(check_valid_pos(new_coords)){
            coords = {new_coords};
            update_block_pos(coords, type);
        }
    }



};

bool check_valid_pos(vector<pair<int,int>>curr_coords){ //check if B is in valid position on board
    
    //int row, col;

    for(pair<int,int>pos:curr_coords){

        if(pos.first <= -1 || pos.second <= -1){
            return false;
        }

        if(pos.first < 1 || pos.first > BOARD_HEIGHT-2){
            return false;
        }
        if(pos.second < 1 || pos.second > BOARD_WIDTH-2){
            return false;
        }
        /*
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
        */
    }
   
    return true;

} 
void update_block_pos(vector<pair<int,int>>coords, int type){

    int piece_found = 0; //max 4
    bool all_found = false; //if 4 found 

    //remove current ones 
    for(int i = 0; i<BOARD_HEIGHT; ++i){
        for(int j = 0; j<BOARD_WIDTH; ++j){
            if(BOARD[i][j] > 1){
                piece_found++;
                BOARD[i][j] = 0;
            }
            if(piece_found == 4){
                all_found = true;
                break;
            }
        }
        if(all_found) break;
    }

    //add new ones
    for(pair<int,int>p:coords){
        BOARD[p.first][p.second] = type;
    }
}
#endif