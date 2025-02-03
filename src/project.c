#include "project.h"

/*
Implementation of functions list

1. The drawing function for drawing inside of the array
    - The draw function should implement the color of each square
    - It should fill the color of each square

After implementing the grid and making it pretty, the rules comes next:

Before the rules:
- We want to be able make a next generation
    Hence we create another array because we wouldn't want to rely on the
    new state of the neighbour but rather the old state when it gets changed
    in terms of states

2. Function for counting the live neighbours
    - This can be a function or not
    - Use mathematical arithmetic

3. Look at the state of the neighbours and the live cell



For dynamic arrays:
1. Calculate for the columns and rows using width and height divided by the resolution

*/

int main(int argc, char* argv[]) {
    int min, max;

    SDL_Window* window = NULL; 

    //Create the 2d array
    grid_row = 10;
    grid_col = 10;
    grid = create_2d_array(grid_row, grid_col);

    min = 0;
    max = 1;
    for (i = 0; i < grid_row; i++) {
        for (j = 0; j < grid_col; j++) {
            grid = (int**) (rand() % (max-min + 1) + min);
        }
    }
    init_SDL(window);
    
    //Render the grid
    render_grid(&grid, grid_row, grid_col, window);

}

//Initalize the SDL2 window
init_SDL(SDL_Window* window) {
        if (SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
        {
            printf("SDL could not initialize: %s\n", SDL_GetError());
        }
        else {
            SDL_Surface* screen_surface = SDL_GetWindowSurface( window );
            window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
            
            if (window == NULL) {
                printf("Windows Null bruh: %s\n", SDL_GetError());
            }
            else {
            SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
        
            SDL_UpdateWindowSurface(window);

            SDL_Event e; 
            bool quit = false;
            while( quit == false )
            { while( SDL_PollEvent( &e ) ) { 
            if( e.type == SDL_QUIT ) { 
                quit = true;
                    } 
                }
            }
        }

        SDL_DestroyWindow(window);

        SDL_Quit();
        
        return 0;
    }
}

//Initialize a 2D array
**create_2d_array(int row, int col) {
    //Create a fixed 2D array
    //Challenge: Make this dynamically grow with user's input
    int** two_dee_array = (int**)malloc(row*sizeof(int*));

    for (i = 0; i < row; i++) {
        two_dee_array[i] = (int*)malloc(col*sizeof(int*));
    }
    return two_dee_array;
}

//Render the boxes on the grid
render_grid(int ***grid, int row, int col, SDL_Window* window) {
    SDL_Surface* screen_surface = SDL_GetWindowSurface( window );

    int i, j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            SDL_Rect* box_rect;
            box_rect->x = i* CELL_HEIGHT;
            box_rect->y = j* CELL_WIDTH;
            box_rect->w = CELL_WIDTH;
            box_rect->h = CELL_HEIGHT;

            //If both the row and columns are high, then we fill it with 
            //the color black (0, 0, 0)
            if (*grid[i][j] == 1) {
                if (SDL_FillRect(screen_surface, box_rect, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00)) != 0) {
                    printf("Error: %s\n", SDL_GetError());
                }
            }
        }
    }
}


