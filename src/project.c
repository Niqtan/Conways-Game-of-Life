#include "project.h"

int main(int argc, char* argv[]) {
    //Debugging
    log_file = fopen("debug.txt", "w+");
    if (log_file == NULL) {
        fprintf(log_file, "Failed to initialize the debugger\n");
        fflush(log_file);
    }
    
    //2D Array variables
    grid_row = 10;
    grid_col = 10;

    //Initialize the first 2d array
    grid = create_2d_array(grid_row, grid_col);
    if (grid == NULL) {
        fprintf(log_file, "Failed to initialize 2D Grid\n");
        fflush(log_file);
        return 1;
    }
    min = 0;
    max = 1;

    for (i = 0; i < grid_row; i++) {
        for (j = 0; j < grid_col; j++) {
            grid[i][j] = rand() % (max-min + 1) + min;
        }
    }

    //Create a var with data type SDL_Window which
    //can either return an instance of window or NULL 
    SDL_Window* window = init_SDL();
    if (window == NULL) {
        fprintf(log_file, "Failed to initialize SDL\n");
        fflush(log_file);
        return 1;
    }

    //Initialize 
    render_grid(grid, grid_row, grid_col, window);

    //An event to not close out the window unless
    //the X button on the top right has been pressed
    SDL_Event e; 
        bool quit = false;
        while( quit == false )
        { while( SDL_PollEvent( &e ) ) { 
        if( e.type == SDL_QUIT ) { 
            quit = true;
            } 
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    fclose(log_file);

    return 0;
}

//Initalize the SDL2 window
SDL_Window* init_SDL() {
    SDL_Window* window = NULL;
    if (SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
    {
        fprintf(log_file, "Failed to initialize SDL: %s\n", SDL_GetError());
        fflush(log_file);
        return;
    }
    else {
        window = SDL_CreateWindow( "Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        if (window == NULL) {
            fprintf(log_file, "Failed to see window: %s\n", SDL_GetError());
            fflush(log_file);
        }
        else {
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            fprintf(log_file, "Failed to initialize the renderer.");
            fflush(log_file);
            return;
        }

        SDL_RenderFillRect(renderer, NULL);
    
        SDL_UpdateWindowSurface(window);
        }
    }

    return window;
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
render_grid(int **grid, int row, int col, SDL_Window* window) {
    
    if (grid == NULL OR window == NULL) {
        fprintf("NULL Pointer in render grid=%p, window=%p\n", (void*)grid, (void*) window);
        fflush(log_file);
        return;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(log_file, "Failed to initialize the renderer.");
        fflush(log_file);
        return;
    }

    int i, j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            SDL_Rect* box_rect;
            if (box_rect == NULL) {
                fprintf(log_file, "Failed to initialize the rectangle.");
                fflush(log_file);
            }
    
            //Map out each of the specifications on the grid
            box_rect->x = i* CELL_HEIGHT;
            box_rect->y = j* CELL_WIDTH;
            box_rect->w = CELL_WIDTH;
            box_rect->h = CELL_HEIGHT;

            //If both the row and columns are 1 (alive cell), then we fill it with 
            //the color black (0, 0, 0)
            if (grid[i][j] == 1) {
                //Fill rect returns 0 if it successful
                if (SDL_RenderFillRect(renderer, box_rect) != 0) {
                    fprintf(log_file, "Failed to fill the rectangle: %s\n", SDL_GetError());
                    fflush(log_file);
                    return;
                }
            }
        }
    }
    
    //Create another grid for the next generation
        /* Why?
        * Reasoning: Once we implement the rules (which is basing a cell's life on its neighbours),
        then it is needed because the next generation will be the current generation which will also
        be needed in determining the state of the current generation
        */
    next_gen_grid = create_2d_array(row, col);

    //Loop over the next generation (this goes on and on)
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {    
            
            //Dealing with the edges
            if ((i > row) OR (j > col)) {
                //Condition for checking both rows
                (i > row) ? (i % row) : (j % col);
            }

            if ((i < 0) OR (j < 0)) {
                //Condition for checking both columns
                (i < 0) ? ((i + row) + 1) : (j + col) + 1;
            }
            //Check out: What if both of them have the same condition?
            
            sum = 0;
            neighbours = count_neighbours(grid, i, j);
        
            next_state = grid[i][j];

            if (next_state == 1 AND (neighbours < 2 OR neighbours > 3)) {
                grid[i][j] = 0;
            }
            else if (next_state == 0 AND neighbours == 3) {
                grid[i][j] = 1;
            }
            else {
                grid[i][j] = next_state;
            }
        }
    }
    grid = next_gen_grid;
}

count_neighbours(int **grid, int x, int y) {
   int i, j;

    //Count the neighbours by determining the surroundings
    //of the cell (top right, bottom right, etc.)
   for (i = -1; i < 2; i++) {
    for (j = -1; j < 2; j++) {
        sum += grid[x + i][y + j];  
   }
    sum -= grid[x][y];
    return sum;
    }
}