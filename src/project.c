#include "project.h"

//2D Array variables
int grid_row = SCREEN_WIDTH / 20;
int grid_col = SCREEN_HEIGHT / 20;

//Debugging
FILE* log_file;

struct SDL2 {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect box_rect;
    int** grid;
} foo;


int main(int argc, char* argv[]) {
    int min, max;
    int i, j;

    struct SDL2 *x = &foo;

    log_file = fopen("debug.txt", "w+");
    if (log_file == NULL) {
        fprintf(log_file, "Failed to initialize the debugger\n");
        fflush(log_file);
    }

    //Initialize the first 2d array
    x->grid = create_2d_array(grid_row, grid_col);
    if (x->grid == NULL) {
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
            x->grid[i][j] = (rand() % (max-min + 1)) + min;
        }
    }

    //Create a var with data type SDL_Window which
    //can either return an instance of window or NULL 
    x = init_SDL();
    if (x->window == NULL) {
        fprintf(log_file, "Failed to initialize SDL\n");
        fflush(log_file);
        return 1;
    }

    bool quit = false;

    SDL_Rect box_rect = x->box_rect;    
    //An event to not close out the window unless
    //the X button on the top right has been pressed
    SDL_Event e; 
        while( quit == false )
        {    
        while( SDL_PollEvent( &e ) ) { 
        if( e.type == SDL_QUIT ) { 
            quit = true;
            } 
        }

        //Loop over for animation
        animate_grid(box_rect, x->renderer, x->grid);

        //Delay for program to breathe
        SDL_Delay(50);
    }

    free_2d_array(x->grid, grid_row);
    kill_SDL2(x->window, x->renderer);
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
        return NULL;
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

void animate_grid(SDL_Rect box_rect, SDL_Renderer* renderer, int** grid) {
    int** next_gen_grid;
    int sum, i, j, x, y;
    int neighbours, next_state;
    
    next_gen_grid = create_2d_array(grid_row, grid_col);
    
    //Compute for the final result
    for (i = 0; i < grid_row; i++) {
        for (j = 0; j < grid_col; j++) { 
            
            sum = 0;
            //Count the amount of neighbours the current cell has
            neighbours = count_neighbours(grid, i, j, sum);
            
            //Assign the current state of the cell
            next_state = grid[i][j];

            //Copy it to the next generation grid for comparison
            if (next_state == 1 AND (neighbours < 2 OR neighbours > 3)) {
                next_gen_grid[i][j] = 0;
            }
            else if (next_state == 0 AND neighbours == 3) {
                next_gen_grid[i][j] = 1;
            }
            else {
                next_gen_grid[i][j] = next_state;
            }
        }
    }

    //Final result
    for (i = 0; i < grid_row; i++) {
        for (j = 0; j < grid_col; j++) {        
            grid[i][j] = next_gen_grid[i][j];;
        }
    }
    free_2d_array(next_gen_grid, grid_row);

    for (x = 0; x <= SCREEN_HEIGHT; x += CELL_HEIGHT) {
        SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
    }

    //Draw the horizontal lines
    for (y = 0; y <= SCREEN_WIDTH; y += CELL_WIDTH) {
        SDL_RenderDrawLine(renderer, 0, y , SCREEN_WIDTH, y);
    }
    //Draw that final result
    for (i = 0; i < grid_row; i++) {
        for (j = 0; j < grid_col; j++) {
            
            //Modify the existing boxes
            box_rect.x = i * CELL_WIDTH;
            box_rect.y = j * CELL_HEIGHT;
            box_rect.w = CELL_WIDTH;
            box_rect.h = CELL_HEIGHT;

            if (grid[i][j] == 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }
            else  {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            }

            if (SDL_RenderFillRect(renderer, &box_rect) != 0) {
                fprintf(log_file, "Failed to fill the rectangle: %s\n", SDL_GetError());
                fflush(log_file);
                return;
            }
        }
    }
    SDL_RenderPresent(renderer);         
}

int count_neighbours(int **grid, int x, int y, int sum) {
   int i, j;
   int row, col;

    //Count the neighbours by determining the surroundings
    //of the cell (top right, bottom right, etc.)
   
    //Bonus: you may experiment with the values of i and j as conditions
    // just to check what other cellular automata you can get
     for (i = -1; i < 2; i++) {
    for (j = -1; j < 2; j++) {

        //Algorithm here is that we should get the position of the current cell
        //and add that to the ith neighbour, relative to the grid row or column.
        row = (x + i + grid_row) % grid_row;
        col = (y + j + grid_col) % grid_col;

        fprintf(log_file, "rows: %d, cols: %d\n", row, col);
        fflush(log_file);

        sum += grid[row][col];  
        }
    }

    //Exclude the current cell as neighbour
    sum -= grid[x][y];
    return sum;
}