
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>

using namespace std;
/*
#include "board.h"
#include "piece.h"
void ok_game(){
    printf("FROM GAME.H\n");
}


int SCORE = 0;

void GAME();
void loop();

block curr_block;
vector<block> blocks;


bool check_game_over();


// method to check if the game is over
bool check_game_over() {
    // check if the first row has any blocks in it
    for (int j = 1; j < BOARD_WIDTH-1; j++) {
        if (BOARD[1][j] != 0) {
            return true;
        }
    }

    return false;
}

// constructor for the game class
void GAME() {
    // initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    // set the seed for the random number generator
    srand(time(NULL));

    // define the color pairs for each block type
    init_pair(2, COLOR_RED, COLOR_RED);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(5, COLOR_BLUE, COLOR_BLUE);
    init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(7, COLOR_CYAN, COLOR_CYAN);

    // initialize the current block and the block vector
    curr_block.type = curr_block.generate_piece();
   
    // draw the board and the current block
    draw_board();

}

// main game loop
void loop() {
    while (!BOARD.isGameOver()) {
        // check for user input
        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                curr_block.moveLeft();
                break;
            case KEY_RIGHT:
                curr_block.moveRight();
                break;
            case KEY_DOWN:
                curr_block.moveDown();
                break;
            case SPACE:
                curr_block.rotate();
                break;
            case 'q':
                endwin();
                return;
    }
}

*/

#endif