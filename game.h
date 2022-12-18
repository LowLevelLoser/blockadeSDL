#ifndef GAME_H_
#define GAME_H_

#define N 4 //number of rows change at will personally I think 4 is the best and the higher you go the worse it gets
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define CELL_WIDTH (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)

#define EMPTY 0
#define P_RED 1
#define P_BLUE 2
#define P_GRAY 4

#define P_GRAY_LIMIT N

#define RUNNING_STATE 0
#define P_RED_WON 1
#define P_BLUE_WON 2
#define TIE_STATE 3
#define QUIT_STATE 4

typedef struct {
	int board[N][N];
	int player;
	int previous_played_red[2];
	int previous_played_blue[2];
	int previous_played_gray[2];
	int p_red_counter;
	int p_blue_counter;
	int p_gray_counter;
	int p_red_moves;
	int p_blue_moves;
	int p_gray_moves;
	int state;
} game_t;


#endif // GAME_H_
