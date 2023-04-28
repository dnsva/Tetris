#ifndef BOARD_FNS_H
#define BOARD_FNS_H

#include <iostream>
#include "classes.h"
#include <ncurses.h>
#include <vector>
#include <utility>
#include "score.h"

using namespace std;


void init_board(){ //initialize all the bottom row to act like blocks (for collision)

    for(int i = 0; i<BOARD_HEIGHT; ++i){
        for(int j = 0; j<BOARD_WIDTH; ++j){
            BOARD[i][j] = 0;
        }
    }
    for(int i = 1; i<BOARD_WIDTH-1; ++i){
        BOARD[BOARD_HEIGHT-1][i] = 1;
    }

    /*
    //make edges off-limit so -1
    for(int i = 1; i<BOARD_WIDTH-1; ++i){
        BOARD[0][i] = -1;
    }
    for(int i = 1; i<BOARD_HEIGHT-1; ++i){
        BOARD[i][0] = -1;
    }
    for(int i = 1; i<BOARD_HEIGHT-1; ++i){
        BOARD[i][BOARD_WIDTH-1] = -1;
    }*/

}

void clear_board(){
    //Reset EVERYTHING 
    init_board();
    SCORE = 0;
}

void draw_board(){
    //DRAW BORDERS & COLORR
    clear(); //clear everything before just in case 

    for (int i = 0; i < BOARD_HEIGHT; i++) {

        int j2 = 0;

        for (int j = 0; j < BOARD_WIDTH; j++) {
                
            

            int color = BOARD[i][j];
            if (color > 0 && i != BOARD_HEIGHT-1) {
                attron(COLOR_PAIR(color));
                
                //char const* u = "\u25A1";
            
                //mvprintw(i,j, "%s", u);

                char const* u = "█";
                mvprintw(i,j2, "%s%s", u ,u);

                //mvaddch(i,j,(char)219);

                //wchar_t mychar = L'\u25A1';
                // print the character using wprintw
                //mvprintw(i,j, "%lc\n", mychar);
                //wprintw(stdscr, "%lc\n", mychar);
                //mvprintw(i, j, "□");
                attroff(COLOR_PAIR(color));
            }else{
               // attrset(A_NORMAL); //reset everything just in case 
               attroff(COLOR_PAIR(color));
                mvprintw(i, j2, "  ");
            }

            if (i == 0 || i == BOARD_HEIGHT-1 || j == 0 || j == BOARD_WIDTH-1) {

                if(i == 0 && j == 0){
                    mvprintw(i, j2," ╔");
                }else if(i == 0 && j == BOARD_WIDTH-1){
                    mvprintw(i, j2,"╗ ");
                }else if(i == BOARD_HEIGHT-1 && j == 0){
                    mvprintw(i, j2," ╚");
                }else if(i == BOARD_HEIGHT-1 && j == BOARD_WIDTH-1){
                    mvprintw(i, j2,"╝ ");
                }else if(i == 0 || i == BOARD_HEIGHT-1){
                    mvprintw(i, j2,"══");
                }else{
                    if(j == 0){
                        mvprintw(i, j2, " ║"); 
                    }else{
                        mvprintw(i, j2, "║ "); 
                    }
                    
                }
                //mvprintw(i, j2, "##");
            }

            j2 += 2;

            

            
        }
    }

    mvprintw(1, BOARD_WIDTH*2 + 1, "SCORE: %d", SCORE);
    mvprintw(2, BOARD_WIDTH*2 + 1, "HIGH SCORE: %d", read_score(DIFFICULTY));

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

            //another full row could have moved down so ++i to recheck row in case
            ++i;
        }
    }

    // if any rows were cleared, update the score
    if (rows_cleared_num > 0) {
        SCORE += rows_cleared_num * 10;
        //mvprintw(BOARD_HEIGHT+2, 2, "Score: %d", SCORE);
    }


}

bool check_game_over(){
    //check if the first row has blocks
    for (int j = 1; j < BOARD_WIDTH-1; j++) {
        if (BOARD[1][j] == 1 ) {
            clear();
            printw("GAME OVER.\n");
            printw("YOUR SCORE WAS: %d\n", SCORE);
            printw("\n[To close press any key]\n");
            int ch = getch();
            mvprintw(3, 0, "[To confirm again to close press any key]\n");
            ch = getch();
            mvprintw(3, 0, "[To FOR SURE confirm again to close press any key]\n");
            ch = getch();
            return true;
        }
    }
    return false;
}

/*

bool check_game_over(const std::vector<std::vector<int>>& board) {
    // Check if any blocks in the top row of the board are occupied
    for (int i = 0; i < board[0].size(); i++) {
        if (board[0][i] != 0) {
            return true;
        }
    }
    return false;
}
*/

#endif

