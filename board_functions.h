#ifndef BOARD_FNS_H
#define BOARD_FNS_H

#include <iostream>
#include "classes.h"
#include <ncurses.h>
#include <vector>
#include <utility>

using namespace std;

void draw_board(){
    //DRAW BORDERS & COLORR
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {

            int color = BOARD[i][j];
            if (color > 0) {
                attron(COLOR_PAIR(color));
                mvprintw(i, j, " ");
                attroff(COLOR_PAIR(color));
            }
            
            if (i == 0 || i == BOARD_HEIGHT-1 || j == 0 || j == BOARD_WIDTH-1) {
                mvprintw(i, j, "#");
            } else {

                if(BOARD[i][j] != 0){
                    
                }else{
                    mvprintw(i, j, " ");
                }
                
            }

            
        }
    }
}



void add_block(block B){ //add block to board
    for(pair<int,int>p : B.coords){
        BOARD[p.first][p.second] = B.type;
    }
}

void clear_rows(){ //clear full rows

    int rows_cleared_num = 0;
    for (int i = BOARD_HEIGHT-2; i > 0; --i){
        // check if the row is full
        bool is_full = true;
        for (int j = 1; j < BOARD_WIDTH-1; j++) {
            if (BOARD[i][j] == 0) {
                is_full = false;
                break;
            }
        }
        // if the row is full, clear it and move all the blocks above it down one row
        if (is_full) {
            rows_cleared_num++;
            for (int k = i; k > 0; k--) {
                for (int j = 1; j < BOARD_WIDTH-1; j++) {
                BOARD[k][j] = BOARD[k-1][j];
                }
            }
            // set the top row to all zeros
            for (int j = 1; j < BOARD_WIDTH-1; j++) {
                BOARD[0][j] = 0;
            }
            // redraw the board
            draw_board();
        }
    }
    // if any rows were cleared, update the score
    if (rows_cleared_num > 0) {
        SCORE += rows_cleared_num * 10;
        mvprintw(BOARD_HEIGHT+2, 2, "Score: %d", SCORE);
    }


}

#endif