#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "snake.h"

void
initialize(int *row, int *col) {
	initscr();
	getmaxyx(stdscr, *row, *col);
	raw();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	srandom(time(NULL));
}

int
main(int argc, char *argv[]) {
	unsigned char done = 0;
	unsigned int input = 1;
	char str[80];
	int row, col;
	int i;
	int chance_to_change = 15;
	int n_snakes = 1;
	initialize(&row, &col);
	//start_color();
	//init_pair(1, COLOR_CYAN, COLOR_BLACK);
	t_snake *snakes = malloc(sizeof(t_snake) * n_snakes);
	for (i = 0; i < n_snakes; i++) {
		snakes[i].y = random() % row;
		snakes[i].x = random() % col;
		snakes[i].facing = random() % 4;
		mvaddch(snakes[i].y, snakes[i].x, '@');
	}
	while (!done) {
		for (int i = 0; i < n_snakes; i++) {
			int try_to_change = random() % 100;
			if (try_to_change <= chance_to_change)
				snakes[i].facing = (snakes[i].facing + try_to_change % 2 ? 1 : -1) % 4;
			snakes[i].y = (snakes[i].y + offsets[snakes[i].facing][Y_OFFSET]) % row;
			snakes[i].x = (snakes[i].x + offsets[snakes[i].facing][X_OFFSET]) % col;
			mvaddch(snakes[i].y, snakes[i].x, '@');
		}
		input = getch();
		if (input == 27) {
			done = 1;
			break;
		}
		//attron(COLOR_PAIR(1));
		//attroff(COLOR_PAIR(1));
	}
	endwin();
	return 0;
}
#include <string.h>
