#include <time.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "snake.h"

void
initialize(int *row, int *col) {
    setlocale(LC_ALL, "");
	initscr();
	getmaxyx(stdscr, *row, *col);
	raw();
	noecho();
	keypad(stdscr, TRUE);
	//nodelay(stdscr, TRUE);
	halfdelay(1);
	curs_set(0);
	srandom(time(NULL));
}

int
clamp(int min, int max, int *val) {
	if (*val < min)
		*val = max;
	else if (*val > max)
		*val = min;
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
	//start_color();
	//init_pair(1, COLOR_CYAN, COLOR_BLACK);
	initialize(&row, &col);

	int symbols[13] = {
		0x2557,				// RIGHT_TO_DOWN,
		0x2550,				// RIGHT,
		0x255D,				// RIGHT_TO_UP,
		0x2554,				// UP_TO_RIGHT,
		0x2551,				// UP,
		0x2557,				// UP_TO_LEFT,
		0x255A,				// LEFT_TO_UP,
		0x2550,				// LEFT,
		0x2554,				// LEFT_TO_DOWN,
		0x255D,				// DOWN_TO_LEFT,
		0x2551,				// DOWN,
		0x255A				// DOWN_TO_RIGHT,
	};

	t_snake *snakes = malloc(sizeof(t_snake) * n_snakes);
	for (i = 0; i < n_snakes; i++) {
		snakes[i].y = random() % row;
		snakes[i].x = random() % col;
		snakes[i].facing = random() % 4;
	}

	getmaxyx(stdscr, row, col);
	while (!done) {
		for (int i = 0; i < n_snakes; i++) {
			int try_to_change = random() % 100;
			char symbid = facing_masks[snakes[i].facing];
			if (try_to_change <= chance_to_change) {
				char direction = (try_to_change % 2 == 0) ? 1 : -1;
				snakes[i].facing += direction;
				symbid += direction;
			}
			mvprintw(snakes[i].y, snakes[i].x, "%lc", symbols[symbid]);
			snakes[i].y += offsets[snakes[i].facing][Y_OFFSET];
			clamp(0, row - 1, &snakes[i].y);
			snakes[i].x += offsets[snakes[i].facing][X_OFFSET];
			clamp(0, col - 1, &snakes[i].x);
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
