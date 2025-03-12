#define Y_OFFSET 0
#define X_OFFSET 1

const int offsets[4][2] = {
	{0, 1},
	{-1, 0},
	{0, -1},
	{1, 0}
};
char facing_masks[] = {1, 4, 7, 10};
enum FACING {
	F_R,
	F_U,
	F_L,
	F_D
};

int double_ended_pipes[13] = {
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

int classic_ascii[13] = {
	'\\',
	'-',
	'/',
	'/',
	'|',
	'\\',
	'\\',
	'-',
	'/',
	'/',
	'|',
	'\\'
};

int alphanumerical[13] = {
	'7',				// RIGHT_TO_DOWN,
	'S',				// RIGHT,
	'J',				// RIGHT_TO_UP,
	'4',				// UP_TO_RIGHT,
	'A',				// UP,
	'7',				// UP_TO_LEFT,
	'L',				// LEFT_TO_UP,
	'S',				// LEFT,
	'4',				// LEFT_TO_DOWN,
	'J',				// DOWN_TO_LEFT,
	'V',				// DOWN,
	'L'				// DOWN_TO_RIGHT,
};

int *charsets[] = {double_ended_pipes, classic_ascii, alphanumerical};

typedef struct snake {
	int x, y;
	enum FACING facing : 2;
	int color_id;
	int chars;
}t_snake;

typedef struct charset {
	int symbols[14];
}t_charset;
