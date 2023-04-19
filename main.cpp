

#include <iostream>

using namespace std;

#include <ncurses.h>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include "classes.h"
#include "board_functions.h"

void ascii();
int menu();
void loop();

int main(){	

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

	printw("Hello World !!!");	
	refresh();

	bool quit = menu();
	while(!quit){
		quit = menu();
	}

	getch();			
	endwin();	


	
	return 0;
}

bool menu(){ //true if we want to quit 

	cout<<"WELCOME TO TETRIS";
	cout<<"WHAT DO YOU WANT TO DO? \n";
	int choice;
	cout<<"[0] - PLAY\n";
	cout<<"[1] - SEE HOW TO PLAY\n";
	cout<<"[2] - QUIT\n";
	cout<<"> ";

	cin>>choice;
	while(choice < 0 || choice > 2){
		cout<<"BAD INPUT, TRY AGAIN\n> ";
		cin>>choice;
	}

	if(choice == 0){ //PLAY
		ascii();
		while(1){
			bool is_done = loop();
			if(is_done){
				break;
			}
		}
		cout<<"YOUR SCORE WAS "<<score<<"\n";
	}else if(choice == 1){ //RULES
		cout<<"RULES:\n";
		cout<<"ASJDFKSDHFKJSDF\n";
	}else{ //QUIT
		return true;
	}

	return false;

}
bool loop(){ //true when game is doen 

	block ACTIVE_PIECE;
	ACTIVE_PIECE.generate_block();

	draw_board();
	add_block(ACTIVE_PIECE);

	while(1){
		//see if game over
		bool is_game_over = check_game_over();
		if(is_game_over){
			return true; //game is over 
		}
		//see if collision happened 
		//if yes make piece to 1s so as if it does not exist
		if(ACTIVE_PIECE.check_collision()){
			return false; //this turn is OVER 
		}

		// check for user input
        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                curr_block.move_LEFT();
                break;
            case KEY_RIGHT:
                curr_block.move_RIGHT();
                break;
            case KEY_DOWN:
                curr_block.move_DOWN();
                break;
            case SPACE:
                curr_block.rotate_block();
                break;
            case 'q':
                endwin();
                return;

		clear_rows(); //clear rows if anything is full 


	}
	

}

void ascii(){                                                        
	cout<<"               __.....__                      .--.     \n";     
	cout<<"           .-''         '.                    |__|       \n";   
	cout<<"     .|   /     .-''\"'-.  \`.      .|  .-,.--. .--.       \n";   
	cout<<"   .' |_ /     /________\   \   .' |_ |  .-. ||  |        \n";  
	cout<<" .'     ||                  | .'     || |  | ||  |     _    \n";
	cout<<"'--.  .-'\\    .-------------''--.  .-'| |  | ||  |   .' |   \n";
	cout<<"   |  |   \\    '-.____...---.   |  |  | |  '- |  |  .   | / \n";
	cout<<"   |  |    \`.             .'    |  |  | |     |__|.'.'| |/\/ \n";
	cout<<"   |  '.'    \`''-...... -'      |  '.'| |       .'.'.-'  /  \n";
	cout<<"   |   /                        |   / |_|       .'   \\_.'   \n";
	cout<<"   \`'-'                         \`'-'                        \n";
}