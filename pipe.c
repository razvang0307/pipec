#include <time.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "snake.h"

#define ESCAPE 27


void
initialize_snakes(int row, int col, t_snake *snakes, int n_snakes) {
	for (int i = 0; i < n_snakes; i++) {
		snakes[i].y = random() % row;
		snakes[i].x = random() % col;
		snakes[i].facing = random() % 4;
		snakes[i].color_id = random() % 7;
		snakes[i].chars = random() % 3;
	}
}

void
initialize(int *row, int *col, t_snake *snakes, int n_snakes) {
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
	start_color();
	initialize_snakes(*row, *col, snakes, n_snakes);
}

void
clamp(int min, int max, int *val) {
	if (*val < min)
		*val = max;
	else if (*val > max)
		*val = min;
}

void
handle_input(int input, unsigned char *done, int row, int col, t_snake **snakes, int *n_snakes, int *last_allocated_snakes, char *paused) {
	switch (input) {
		case ESCAPE:
			*done = 1;
			return;
		case 'r':
		case 'R':
			erase();
			initialize_snakes(row, col, *snakes, *n_snakes);
			return;
		case 'p':
		case 'P':
			*paused = !(*paused);
			return;
		case '+':
			*n_snakes = *n_snakes + 1;
			if (*n_snakes > *last_allocated_snakes) {
				t_snake *temp = malloc(sizeof(t_snake) * 2 * (*last_allocated_snakes));
				memcpy(temp, *snakes, sizeof(t_snake) * (*last_allocated_snakes));
				*last_allocated_snakes = (*last_allocated_snakes) * 2;
				free(*snakes);
				*snakes = temp;
			}
			t_snake *current_snake = *snakes + ((*n_snakes) - 1);
			current_snake->y = random() % row;
			current_snake->x = random() % col;
			current_snake->facing = random();
			current_snake->color_id =  random() % 7;
			current_snake->chars =  random() % 2;
			return;
		case '-':
			if (*n_snakes)
				*n_snakes = *n_snakes - 1;
			return;
	}
}

int
main(int argc, char *argv[]) {
	unsigned char done = 0;
	unsigned int input = 1;
	int row, col;
	int chance_to_change = 15;
	int n_snakes = 1;
	int last_allocated_snakes = n_snakes;
	//start_color();
	//init_pair(1, COLOR_CYAN, COLOR_BLACK);
	t_snake *snakes = malloc(sizeof(t_snake) * n_snakes);
	initialize(&row, &col, snakes, n_snakes);

	char paused;

	init_pair(0, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);

	getmaxyx(stdscr, row, col);
	while (!done) {
		getmaxyx(stdscr, row, col);
		input = getch();
		if (input != -1)
			handle_input(input, &done, row, col, &snakes, &n_snakes, &last_allocated_snakes, &paused);
		if (paused)
			continue;
		for (int i = 0; i < n_snakes; i++) {
			int try_to_change = random() % 100;
			char symbid = facing_masks[snakes[i].facing];
			if (try_to_change <= chance_to_change) {
				char direction = (try_to_change % 2 == 0) ? 1 : -1;
				snakes[i].facing += direction;
				symbid += direction;
			}
			attron(COLOR_PAIR(snakes[i].color_id));
			mvprintw(snakes[i].y, snakes[i].x, "%lc", charsets[snakes[i].chars][(int)symbid]);
			attroff(COLOR_PAIR(snakes[i].color_id));
			snakes[i].y += offsets[snakes[i].facing][Y_OFFSET];
			clamp(0, row - 1, &snakes[i].y);
			snakes[i].x += offsets[snakes[i].facing][X_OFFSET];
			clamp(0, col - 1, &snakes[i].x);
		}
	}
	free(snakes);
	endwin();
	return 0;
}
