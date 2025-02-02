#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#include "header.h"

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

enum {
    row = 10,
    col = 10
};

int** grid;
int i, j;


int main(int argc, char* args[]) {
    int min, max;

    SDL_Window* window = NULL;

    //Create the 2d array
    grid = create_2d_array(row, col);

    min = 0;
    max = 1;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            grid = rand() % (max-min + 1) + min;
        }
    }

    if ((init_SDL(window)) != 0) {
        return -1;
    }
    else {
    //Render the grid
    render_grid(&grid, row, col);

    SDL_DestroyWindow(window);

    SDL_Quit();
    }
}