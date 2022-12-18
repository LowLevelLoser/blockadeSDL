#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "./game.h"
#include "./logic.h"
#include "./rendering.h"

int main(int arc, char *argv[]){
	//Initializes SDL returns an error if it cant
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//initializes a window
    SDL_Window *window = SDL_CreateWindow("Blockade",
 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, //position
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
	// return error if it cannot create window
	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	//abstract object that does rendereing in the window black magic
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
			                                    SDL_RENDERER_ACCELERATED |
												SDL_RENDERER_PRESENTVSYNC);
	//error
	if(renderer == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	game_t game = {
		//.board = { {EMPTY, EMPTY, EMPTY, EMPTY},
		//		   {EMPTY, EMPTY, EMPTY, EMPTY},
		//		   {EMPTY, EMPTY, EMPTY, EMPTY},
		//		   {EMPTY, EMPTY, EMPTY, EMPTY}},
		.player = P_RED,
		.p_red_counter = 0,
		.p_blue_counter = 0,
		.p_gray_counter = 0,
		.p_red_moves = 1,
		.p_blue_moves = 1,
		.p_gray_moves = 1,
		.state = RUNNING_STATE

	};

	//checks if you haven't quit the window
	SDL_Event e; // this has the events
	while(game.state != QUIT_STATE){
		while (SDL_PollEvent(&e)){
			switch (e.type){
			case SDL_QUIT:
					game.state = QUIT_STATE;
					break;
			case SDL_MOUSEBUTTONDOWN:
				click_on_cell(&game, e.button.y / CELL_HEIGHT, e.button.x / CELL_WIDTH, e.button.button);
				break;//*/
				default: {}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0/*R*/, 0/*G*/, 0/*B*/, 255); //makes the background black
		SDL_RenderClear(renderer); //makes rendereing visible double buffering
		
		render_game(renderer, &game);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
