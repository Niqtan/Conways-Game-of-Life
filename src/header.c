#include <stdio.h>
#include <SDL.h>
#include <header.c>
#include <stdlib.h>

int i, j;

int init_SDL() {
        SDL_Window* window = NULL;
        SDL_Surface* screen_surface = NULL;

        if (SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
        {
            printf("SDL could not initialize: %s\n", SDL_GetError());
        }
        else {

            window= SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
            
            if (window == NULL) {
                printf("Windows Null bruh: %s\n", SDL_GetError());
            }
            else {
            screen_surface = SDL_GetWindowSurface( window );

            SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
        
            SDL_UpdateWindowSurface(window);

            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
            }
        }

        return 0;
}


//Initialization function
int** create_2d_array(int row, int col) {
    //Create a fixed 2D array
    //Challenge: Make this dynamically grow with user's input
    int** two_dee_array = (int**)malloc(row*sizeof(int*));

    for (i = 0; i < row; i++) {
        two_dee_array[i] = (int*)malloc(col*sizeof(int*));
    }
    return two_dee_array;
}

//Rendering Function
int render_grid(char ***grid, int row, int col) {
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            SDL_Surface* one_grid = grid[i][j];
            SDL_Rect* box_rect = col;

            if (grid[i][j] == 1) {
                if (SDL_FillRect(one_grid, box_rect, SDL_MapRGB(one_grid->format, 0x00, 0x00, 0x00)) != 0) {
                    printf("Error: %s\n", SDL_GetError());
                }
            }
        }
    }
}

int count_neighbors() {
    
}