#include "./game.h"
#include "./logic.h"
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL_mouse.h>

void player_turn(game_t *game, int row, int column, int button);
bool check_if_available(int counter, int row, int column, int previous_played[2]);
int check_around(game_t *game, int previous_played[2]);
void check_moves(game_t *game);
void do_when_no_moves(game_t *game);

void click_on_cell(game_t *game, int row, int column, int button){
	if (game->state == RUNNING_STATE){
		player_turn(game, row, column, button);

	}
	else{ // resets
		for(int x = 0; x < N; x++){
			for(int y = 0; y < N; y++){
				game->board[x][y] = EMPTY;
			}
		}
		game->player = P_RED;
		game->p_red_counter = 0,
		game->p_blue_counter = 0,
		game->p_gray_counter = 0,
		game->p_red_moves = 1,
		game->p_blue_moves = 1,
		game->p_gray_moves = 1,
		game->state = RUNNING_STATE;
	}
}

void player_turn(game_t *game, int row, int column, int button){
	do_when_no_moves(game);
	if(game->board[column][row] != EMPTY) return;
	//plays the piece updates and switches turn
	if(button == SDL_BUTTON_RIGHT){ 
		if(check_if_available(game->p_gray_counter, row, column, game->previous_played_gray) && (game->p_gray_counter < P_GRAY_LIMIT)){
			game->board[column][row] = P_GRAY;
			game->previous_played_gray[0] = column; 
			game->previous_played_gray[1] = row; 
			game->p_gray_counter++;
			if(game->player == P_RED) game->player = P_BLUE;
			else if(game->player == P_BLUE) game->player = P_RED;
		}
	}
	else{
	if (game->player == P_RED) {
		if(check_if_available(game->p_red_counter, row, column, game->previous_played_red)){
			game->board[column][row] = game->player;
			game->player = P_BLUE;
			game->previous_played_red[0] = column; 
			game->previous_played_red[1] = row; 
			game->p_red_counter++;
		}
	}
	else if (game->player == P_BLUE){
		if(check_if_available(game->p_blue_counter, row, column, game->previous_played_blue)){
			game->board[column][row] = game->player;
			game->player = P_RED;
			game->previous_played_blue[0] = column; 
			game->previous_played_blue[1] = row; 
			game->p_blue_counter++;
		}
	}
	}
	do_when_no_moves(game);
}

void do_when_no_moves(game_t *game){
	check_moves(game);
	//autoswitches turns
	if((game->player == P_RED)&&(game->p_red_moves == 0)) game->player = P_BLUE;
	else if((game->player == P_BLUE)&&(game->p_blue_moves == 0)) game->player = P_RED;
	//win coditions
	if((game->p_red_moves + game->p_blue_moves == 0)){
		if(game->p_red_counter > game->p_blue_counter){
			game->state = P_RED_WON;
		}
		else if(game->p_red_counter < game->p_blue_counter){
			game->state = P_BLUE_WON;
		}
		else{
			game->state = TIE_STATE;
		}
	}//*/
}

bool check_if_available(int counter, int row, int column, int previous_played[2]){
	if(counter == 0) return true;
	if((abs(column - previous_played[0]) <= 1) && (abs(row - previous_played[1]) <= 1)){
		return true;
	}
	return false;
}

void check_moves(game_t *game){ 
	if(game->p_gray_counter != 0){
		if(game->p_gray_counter != P_GRAY_LIMIT){
			game->p_gray_moves = check_around(game, game->previous_played_gray);
		}
		else{
			game->p_gray_moves = 0;
		}
	}

	if(game->p_red_counter != 0){
		game->p_red_moves = check_around(game, game->previous_played_red);
	}

	if(game->p_blue_counter != 0){
		game->p_blue_moves = check_around(game, game->previous_played_blue);
	}

	game->p_red_moves = game->p_red_moves + game->p_gray_moves;
	game->p_blue_moves = game->p_blue_moves  + game->p_gray_moves;
}

int check_around(game_t *game, int previous_played[2]){
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if(!(((previous_played[0]+j >= N)||(previous_played[1]+i >= N))||((previous_played[0]+j < 0)||(previous_played[1]+i < 0)))&&(game->board[previous_played[0]+j][previous_played[1]+i] == EMPTY)){ //checking inside the board				
				
				return 1;

			}
		}
	}
	return 0;
}
