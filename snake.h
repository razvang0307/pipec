#define Y_OFFSET 0
#define X_OFFSET 1

const int offsets[4][2] = {
	{0, -1},
	{0, 1},
	{-1, 0},
	{1, 0}
};

enum FACING {
	F_L,
	F_R,
	F_U,
	F_D
};

enum DISPLAY {
	D_L,
	D_R,
	D_U,
	D_D,
	D_LTU,
	D_LTD,
	D_RTU,
	D_RTD,
	D_UTL,
	D_UTR,
	D_DTL,
	D_DTR
};

typedef struct snake {
	unsigned int x, y;
	enum FACING facing : 2;
}t_snake;

typedef struct charset {
	char symbols[12];
}t_charset;
