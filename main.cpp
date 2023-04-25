

#include <iostream>

using namespace std;

#include <ncurses.h>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include "classes.h"
#include "board_functions.h"
#include <chrono>
#include <thread>

bool menu();
void ascii();
bool loop();

int main(){	

	//ascii(); //ascii art needs to be fixed :(

	// initialize ncurses
	//setenv("LINES","100",1); //make lines thinner
	setlocale(LC_ALL, ""); //enable utf-8
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
	//printw("\033[3;1]"); //resize
    // set the seed for the random number generator
    srand(time(NULL));	

	clear(); //clear the screen


    // define the color pairs for each block type
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN,COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_color(100, 500, 0, 500); // defines a purple color
	init_pair(8, 100, COLOR_BLACK); //purple


	refresh();
	//return 0;


	bool quit = menu();
	while(!quit){
		quit = menu();
	}

	if(quit){
		return 0;
	}

	//getch();			
	endwin();	


	
	return 0;
}

bool menu(){ //true if we want to quit 
	clear(); //clear screen
	printw("WELCOME TO TETRIS...\nWHAT DO YOU WANT TO DO?\n");
	int choice;
	string options[] = {"PLAY", "HOW TO", "QUIT"};
	while(true){
        for (int i = 0; i < 3; i++){ //print list of options
            if (i == choice){
                attron(A_STANDOUT);// highlight the chosen option
            }
            mvprintw(i+1,0,"%d. %s\n", i+1, options[i].c_str());
            attroff(A_STANDOUT);
        }
        int c = getch();
        if (c == KEY_DOWN){
            choice = (choice + 1) % 3;
        }
        else if (c == KEY_UP){
            choice = (choice + 3) % 3;
        }
        else if (c == 10){
			
            attron(A_BOLD);
            attron(A_STANDOUT);
            mvprintw(choice+1, 0, "%d. %s?\n", choice+1, options[choice].c_str());
            int confirm = getch();
            if(confirm == 10){
                this_thread::sleep_for(chrono::milliseconds(500));
                endwin();
                break;
            }else{
                attroff(A_BOLD);
                attroff(A_STANDOUT);
                if (confirm == KEY_DOWN){
                    choice = (choice + 1) % 3;
                }
                else if (confirm == KEY_UP){
                    choice = (choice + 3) % 3;
                }
            }
        }
    }
	//clear(); //clear the screen 
	attrset(A_NORMAL); //reset any highlighted stuff
	

	if(choice == 0){ //PLAY
		clear_board();
		//init_board();
		while(1){
			bool is_done = loop();
			if(is_done){
				break;
			}
		}
		//printw("YOUR SCORE WAS %d\n", SCORE);
	}else if(choice == 1){ //RULES

		clear();
	
		mvprintw(1, 0, "HOW TO PLAY:\n");

		mvprintw(2, 0, "TRY TO GET AS MANY POINTS AS POSSIBLE.\n");
		mvprintw(3, 0, "CONTROLS FOR TETRIS BLOCKS:\n");
		mvprintw(4, 0, "     ---                 ---            \n");  
		mvprintw(5, 0, "    | W |               | ^ |           \n");
		mvprintw(6, 0, "     ---       OR        ---            \n");
		mvprintw(7, 0, " --- --- ---         --- --- ---        \n");
		mvprintw(8, 0, "| A | S | D |       | < | v | > |       \n");
		mvprintw(9, 0, " --- --- ---         --- --- ---        \n");
		printw("You can close your current game at any time by pressing 'q'\n\n");
		printw("[PRESS ANY KEY TO CLOSE THIS WINDOW]\n");
		int ch = getch();

	}else{ //QUIT
		return true;
	}

	return false;

}
bool loop(){ //true when game is doen 

	clear_rows(); //clear rows if anything is full 

	block ACTIVE_PIECE;
	//ACTIVE_PIECE.generate_block();
	ACTIVE_PIECE.generate_block();
	
	add_block(ACTIVE_PIECE);
	draw_board();

	while(1){

		
		
		
		
		// check for user input
        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                ACTIVE_PIECE.move_LEFT();
				//printw("MOVED LEFT???\n");
                break;
            case KEY_RIGHT:
                ACTIVE_PIECE.move_RIGHT();
                break;
            case KEY_DOWN:
                ACTIVE_PIECE.move_DOWN();
                break;
            case KEY_UP:
                ACTIVE_PIECE.rotate_block();
                break;
			case 'a': //left alternative
				ACTIVE_PIECE.move_LEFT();
                break;
			case 'd': //right alternative
				ACTIVE_PIECE.move_RIGHT();
                break;
			case 's': //down alternative
				ACTIVE_PIECE.move_DOWN();
                break;
			case 'w': //rotate alternative
				ACTIVE_PIECE.rotate_block();
                break;
            case 'q':
                endwin();
                return true;
		}

		//see if collision happened 
		//if yes make piece to 1s so as if it does not exist
		if(ACTIVE_PIECE.check_collision()){
			add_block(ACTIVE_PIECE); //rewrite this pos with 1s 
			//draw_board();
			return false; //this turn is OVER 
		}
		draw_board();

		//see if game over
		bool is_game_over = check_game_over();
		if(is_game_over){
			endwin();
			return true; //game is over 
		}


	}
	

}

void ascii(){      
/*
	printw("               __.....__                      .--.     \n");     
	printw("           .-''         '.                    |__|       \n");   
	printw("     .|   /     .-''\"'-.  \`.      .|  .-,.--. .--.       \n");   
	printw("   .' |_ /     /________\   \   .' |_ |  .-. ||  |        \n");  
	printw(" .'     ||                  | .'     || |  | ||  |     _    \n");
	printw("'--.  .-'\\    .-------------''--.  .-'| |  | ||  |   .' |   \n");
	printw("   |  |   \\    '-.____...---.   |  |  | |  '- |  |  .   | / \n");
	printw("   |  |    \`.             .'    |  |  | |     |__|.'.'| |/\/ \n");
	printw("   |  '.'    \`''-...... -'      |  '.'| |       .'.'.-'  /  \n");
	printw("   |   /                        |   / |_|       .'   \\_.'   \n");
	printw("   \`'-'                         \`'-'                        \n");
*/
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

	this_thread::sleep_for(chrono::milliseconds(7000));

}