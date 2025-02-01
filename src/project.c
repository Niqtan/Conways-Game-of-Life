#include <stdio.h>
#include <SDL.h>
#include <header.c>
#include <stdlib.h>


/*
Implementation of functions list

1. The drawing function for drawing inside of the array
    - The draw function should implement the color of each square
    - It should fill the color of each square
    - Perhaps we could use a library for this

After implementing the grid and making it pretty, the rules comes next:

Before the rules:
- We want to be able make a next generation
    Hence we create another array

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

char** grid;
int i, j;

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

int main(int argc, char* args[]) {
    int min, max;

    //Create the 2d array
    grid = create_2d_array(row, col);

    min = 0;
    max = 1;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            grid = rand() % (max-min + 1) + min;
        }
    }

    if ((init_SDL()) != 0) {
        return -1;
    }
    else {
    //Render the grid
    render_grid(&grid, row, col);

    SDL_DestroyWindow(window);

    SDL_Quit();
    }
}
