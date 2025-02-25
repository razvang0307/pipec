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

typedef struct snake {
	int x, y;
	enum FACING facing : 2;
}t_snake;

typedef struct charset {
	int symbols[14];
}t_charset;
