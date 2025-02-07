#include "project.h"

//2D Array variables
int grid_row = SCREEN_WIDTH / 20;
int grid_col = SCREEN_HEIGHT / 20;

//Debugging
FILE* log_file;

struct SDL2 {
    SDL_Window* window;
    SDL_Renderer* renderer;
} foo;

int main(int argc, char* argv[]) {
    int min, max;
    int i, j;

    int** grid;

    log_file = fopen("debug.txt", "w+");
    if (log_file == NULL) {
        fprintf(log_file, "Failed to initialize the debugger\n");
        fflush(log_file);
    }

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

            //The algorithm here is to generate a 1 or 0 depending on the rand num 
            //So that picking of numbers really is random
            grid[i][j] = (rand() % (max-min + 1)) + min;
        }
    }

    //Create a var with data type SDL_Window which
    //can either return an instance of window or NULL 
    struct SDL2* Sigma_Boy = init_SDL();
    if (Sigma_Boy->window == NULL) {
        fprintf(log_file, "Failed to initialize SDL\n");
        fflush(log_file);
        return 1;
    }

    //Initialize 
    render_grid(grid, Sigma_Boy->renderer);

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

    free_2d_array(grid, grid_row);
    kill_SDL2(Sigma_Boy->window, Sigma_Boy->renderer);
    fclose(log_file);

    return 0;
}

//Initalize the SDL2 window
struct SDL2* init_SDL() {

    struct SDL2 *AgentX =  &foo;
    AgentX->window = NULL;
    if (SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
    {
        fprintf(log_file, "Failed to initialize SDL: %s\n", SDL_GetError());
        fflush(log_file);
        return;
    }
    else {
        AgentX->window = SDL_CreateWindow( "Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        if (AgentX->window == NULL) {
            fprintf(log_file, "Failed to see window: %s\n", SDL_GetError());
            fflush(log_file);
        }
        else {
        AgentX->renderer = SDL_CreateRenderer(AgentX->window, -1, SDL_RENDERER_ACCELERATED);
        if (AgentX->renderer == NULL) {
            fprintf(log_file, "Failed to initialize the renderer.");
            fflush(log_file);
            return;
        }

        SDL_SetWindowBordered(AgentX->window, SDL_TRUE);
        SDL_UpdateWindowSurface(AgentX->window);
        SDL_SetRenderDrawColor(AgentX->renderer, 255, 255, 255, 0);
        SDL_RenderClear(AgentX->renderer);
    
        }
    }

    return AgentX;
}

void kill_SDL2(SDL_Window* window, SDL_Renderer* renderer) {
    //Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

//Initialize a 2D array
int **create_2d_array(int row, int col) {
    int i, j;
    int** two_dee_array = (int**)malloc(row*sizeof(int*));

    for (i = 0; i < row; i++) {
        two_dee_array[i] = (int*)malloc(col*sizeof(int));
    }
    return two_dee_array;
}

void free_2d_array(int** array, int row) {
    int i, j;
    for (i = 0; i < row; i++) {
        free(array[i]);
    }
    free(array);
}

//Render the boxes on the grid
int render_grid(int **grid, SDL_Renderer* renderer) {
    int i, j, x, y;
    
    if (grid == NULL OR renderer == NULL) {
        fprintf("NULL Pointer in render grid=%p, renderer=%p\n", (void*)grid, (void*) renderer);
        fflush(log_file);
        return;
    }
    
    if (renderer == NULL) {
        fprintf(log_file, "Failed to initialize the renderer.");
        fflush(log_file);
        return;
    }

    //Clear out the previous backbuffer in order
    //to fill in the white cells
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    if (SDL_RenderClear(renderer) != 0) {
        fprintf(log_file, "Stop giving me seg faults!");
        fflush(log_file);
    }

    
    SDL_Rect box_rect;
    if (&box_rect == NULL) {
        fprintf(log_file, "Failed to initialize the rectangle.");
        fflush(log_file);
        return;
    }

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    
   //Draw the borders
   //Draw vertical lines
   for (x = 0; x <= SCREEN_HEIGHT; x += CELL_HEIGHT) {
        SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
   }

   //Draw the horizontal lines
   for (y = 0; y <= SCREEN_WIDTH; y += CELL_WIDTH) {
        SDL_RenderDrawLine(renderer, 0, y , SCREEN_WIDTH, y);
   }

    //Drawing the rectangles
    for (i = 0; i < grid_row; i++) {
        for (j = 0; j < grid_col; j++) {               
            //Map out each of the specifications on the grid
            if (grid[i][j] == 1) {
                //To align each rectangle like of grid's, modify
                // the x and y values
                box_rect.x = i * CELL_WIDTH;
                box_rect.y = j * CELL_HEIGHT;
                box_rect.w = CELL_WIDTH;
                box_rect.h = CELL_HEIGHT;
            
             //If both the row and columns are 1 (alive cell), then we fill it with 
                //the color white (0, 0, 0)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                if (SDL_RenderFillRect(renderer, &box_rect) != 0) {
                    fprintf(log_file, "Failed to fill the rectangle: %s\n", SDL_GetError());
                    fflush(log_file);
                    return -1;
                    }
                }
            }
        }
          
    SDL_RenderPresent(renderer);
    
    //Create another grid for the next generation
        /* Why?
        * Reasoning: Once we implement the rules (which is basing a cell's life on its neighbours),
        then it is needed because the next generation will be the current generation which will also
        be needed in determining the state of the current generation
        */
    int** next_gen_grid;
    
    next_gen_grid = create_2d_array(grid_row, grid_col);
    
    int sum;
    int neighbours, next_state;
    //Loop over the next generation (this goes on and on)
    
    /*
    To animation this, we could probably use an
    event in SDL events. We want to keep looping until
    all of the cells are considered dead
    
    */
    
    for (i = 0; i < grid_row; i++) {
        for (j = 0; j < grid_col; j++) { 
            
            sum = 0;
            neighbours = count_neighbours(grid, i, j, sum);
        
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
    
            switch (grid[i][j]) {
                case 0: 
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                    break;
                case 1:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                    break;
            }
            
            if (SDL_RenderFillRect(renderer, &box_rect) != 0) {
                fprintf(log_file, "Failed to fill the rectangle: %s\n", SDL_GetError());
                fflush(log_file);
                return -1;
            }
        }
    }
    SDL_RenderPresent(renderer);           
    grid = next_gen_grid;
}

int count_neighbours(int **grid, int x, int y, int sum) {
   int i, j;
   int row, col;

    //Count the neighbours by determining the surroundings
    //of the cell (top right, bottom right, etc.)
   for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
        row = (x + i) % grid_row;
        col = (y + j) % grid_col;

        fprintf(log_file, "row: %d, col: %d\n", row, col);
        fflush(log_file);

        sum += grid[row][col];  
    }
    sum -= grid[x][y];
    }
    return sum;
}