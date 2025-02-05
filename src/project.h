#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>

#define SDL_MAIN_HANDLED

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

#define CELL_WIDTH 10
#define CELL_HEIGHT 10

#define OR ||
#define AND &&

//Debugging
FILE* log_file;


/* Global variables
int i, j: for loop iteration purposes
int grid_row, grid_col: fixed number of rows and columns
int** grid: the 2D array 
*/

int min, max;
int i, j;
int grid_row, grid_col;
int** grid, next_gen_grid;
int sum;
int neighbours, next_state;

/* Init_SDL initalize the SDL2 window
* @return: an affirmation whether the initialization was successful
*/
SDL_Window* init_SDL();

/* create_2d_array: initialize a 2d array with rows and columns
* @param a: the fixed number of rows to work with
* @param b: the fixed number of columns to work with
* @return: the byproduct of the two parameters which is a 2d array for storage
*/
int** create_2d_array(int row, int col);

/* render_grid: uses the 2d array and initializes a grid for the game
* @param a: An address to the working grid which is just a 2D array
* @param b: @param a: the fixed number of rows to work with
* @param c: @param a: the fixed number of columns to work with
* @param d: window to be working on using a pointer to SDL_Window datatype
* @return: confirmation if it was successful
*/
void render_grid(int **grid, int row, int col, SDL_Window* window);

/* count_neighbours: uses an algorithm to count surrounding neighbours position
* @param a: The next generation grid
* @param b: the current column number on the grid
* @param c: the current row number on the grid
* @return: int for the surrounding neighbours
*/
int count_neighbours(int **grid, int x, int y);
