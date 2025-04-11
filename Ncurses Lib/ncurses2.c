
#include <ncurses.h>


int main() 
{
	int x , y;

	//screen initiliaze
	initscr();
	clear();

	//it locates the curser position (current cordinate)  on the screem takes 3 argument
	//current screem : standardscreen (stdscr)  ,  x : var  ,  y : var
	getyx(stdscr , y , x);
	
	printw(  "x = %d\n"
					 "y = %d",
					 x , y);

	//always refresh after printing something on the screen
	refresh();

	y = 5;
	x = 10;

	//this func moves the curser to given cordinate
	move(y , x);
	//this will print start from that cordinate
	printw("Over here!");

	refresh();
	

	getch();
	endwin();

	
	return 0;
}
