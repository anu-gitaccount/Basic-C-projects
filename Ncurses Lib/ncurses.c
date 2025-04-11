
#include <ncurses.h>


int main() {

	char letter;

	//initialize screen (default);
	initscr();

	//ncurses's own print func
	printw("Press any key");
	//to do anything in the screen we have to refresh it
	
	refresh();

	//advanced input method 
	letter = getch();
	clear();

	printw("You pushed: %c", letter);
	refresh();

	getch();
	endwin();
	
	//to compile we have to specify the lib 
	//gcc ncureses.c -o ncurses -lncurses

	return 0;
}
