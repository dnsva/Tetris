
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>
#include <utility>

#include "piece.h"
#include "game.h"

using namespace std;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;


struct BOARD{

    int board[BOARD_HEIGHT][BOARD_WIDTH]; //[r][c]

    BOARD()
        : board{} //initialize ALL values to 0
    {}

    void draw(){
        //DRAW BORDERS & COLORR
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                if (i == 0 || i == BOARD_HEIGHT-1 || j == 0 || j == BOARD_WIDTH-1) {
                    mvprintw(i, j, "#");
                } else {
                    mvprintw(i, j, " ");
                }

                int color = board[i][j];
                if (color > 0) {
                    attron(COLOR_PAIR(color));
                    mvprintw(i, j, " ");
                    attroff(COLOR_PAIR(color));
                }
            }
        }
    }

    

    void add_block(block B){ //add block to board
        for(pair<int,int>p : B.coords){
            board[p.first][p.second] = B.type;
        }
    }

    void clear_rows(){ //clear full rows

        int rows_cleared_num = 0;
        for (int i = BOARD_HEIGHT-2; i > 0; --i){
            // check if the row is full
            bool is_full = true;
            for (int j = 1; j < BOARD_WIDTH-1; j++) {
                if (board[i][j] == 0) {
                    is_full = false;
                    break;
                }
            }
            // if the row is full, clear it and move all the blocks above it down one row
            if (is_full) {
                rows_cleared_num++;
                for (int k = i; k > 0; k--) {
                    for (int j = 1; j < BOARD_WIDTH-1; j++) {
                    board[k][j] = board[k-1][j];
                    }
                }
                // set the top row to all zeros
                for (int j = 1; j < BOARD_WIDTH-1; j++) {
                    board[0][j] = 0;
                }
                // redraw the board
                draw();
            }
        }
        // if any rows were cleared, update the score
        if (rows_cleared_num > 0) {
            SCORE += rows_cleared_num * 10;
            mvprintw(BOARD_HEIGHT+2, 2, "Score: %d", SCORE);
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
        if(board[row][col] != 0){
            return false;
        }
    }

    return true;
}               

#endif