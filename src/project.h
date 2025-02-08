#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>

#define SDL_MAIN_HANDLED

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

#define CELL_WIDTH 20
#define CELL_HEIGHT 20

#define OR ||
#define AND &&

/* Init_SDL initalize the SDL2 window
* @return: an affirmation whether the initialization was successful
*/
struct SDL2* init_SDL();

/* create_2d_array: initialize a 2d array with rows and columns
* @param a: the fixed number of rows to work with
* @param b: the fixed number of columns to work with
* @return: the byproduct of the two parameters which is a 2d array for storage
*/
int** create_2d_array(int row, int col);

/* free_2d_array: frees up the memory allocated for the 2d grid
* @param a: The 2d array created for the 2d grid
* @param b: the number of rows of the 2d array
*/
void free_2d_array(int** array, int row);

/* count_neighbours: uses an algorithm to count surrounding neighbours position
* @param a: The next generation grid
* @param b: the current column number on the grid
* @param c: the current row number on the grid
* @return: int for the surrounding neighbours
*/
int count_neighbours(int** grid, int x, int y, int sum);

/* animate_grid: Implements the rules of Conway's game of life
* @param a: the cells to draw to update
* @param b: the renderer for the final look
* @param c: the grid to handle the backbuffer
*/
void animate_grid(SDL_Rect box_rect, SDL_Renderer* renderer, int** grid);

/* kill_SDL2: destroys the renderer and the window
* @param a: the window to be destroyed
* @param b: the renderer to be killed
*/
void kill_SDL2(SDL_Window* window, SDL_Renderer* renderer);

