#include <SDL2/SDL.h>

#include "./game.h"
#include "./rendering.h"

void render_running_state(SDL_Renderer *renderer, const game_t *game);
void render_grid(SDL_Renderer *renderer);

void render_game(SDL_Renderer *renderer, const game_t *game){
	SDL_Rect game_over_screen;
	game_over_screen.x = 0;
	game_over_screen.y = 0;
	game_over_screen.w = SCREEN_WIDTH;
	game_over_screen.h = SCREEN_HEIGHT;
	switch(game->state){
		case RUNNING_STATE:
			render_running_state(renderer, game);
			break;
		case P_RED_WON:
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &game_over_screen);
			break;
		case P_BLUE_WON:
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderFillRect(renderer, &game_over_screen);
			break;
		case TIE_STATE:
			SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
			SDL_RenderFillRect(renderer, &game_over_screen);
			break;
		default: {}
	}
}


void render_running_state(SDL_Renderer *renderer, const game_t *game){
	SDL_Rect player_piece;
	player_piece.w = CELL_WIDTH;
	player_piece.h = CELL_HEIGHT;
	for(int x = 0; x < N; x++){
		for(int y = 0; y < N; y++){
			switch(game->board[x][y]){
				case P_RED:
					player_piece.x = x*CELL_WIDTH;
					player_piece.y = y*CELL_HEIGHT;
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderFillRect(renderer, & player_piece);
					break;
				case P_BLUE:
					player_piece.x = x*CELL_WIDTH;
					player_piece.y = y*CELL_HEIGHT;
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					SDL_RenderFillRect(renderer, & player_piece);
					break;
				case P_GRAY:
					player_piece.x = x*CELL_WIDTH;
					player_piece.y = y*CELL_HEIGHT;
					SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
					SDL_RenderFillRect(renderer, & player_piece);
					break;

				default: 
					player_piece.x = x*CELL_WIDTH;
					player_piece.y = y*CELL_HEIGHT;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(renderer, & player_piece);
			}
			render_grid(renderer);
		}
	}
}


void render_grid(SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 1; i < N; ++i) {
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,
                           i * CELL_WIDTH, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer,
                           0,            i * CELL_HEIGHT,
                           SCREEN_WIDTH, i * CELL_HEIGHT);
    }
}
