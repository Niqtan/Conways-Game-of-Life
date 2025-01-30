#include <stdio.h>
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

main() {
    int min, max;

    printf("Welcome to...");
    printf(
        "////////////////////////////////////////////////////////\n"
        "///////                                            ///////\n"
        "///////      CONWAY'S GAME OF LIFE IN C            ///////\n"
        "///////                                            ///////\n"
        "///////                BASIC RULES:                ///////\n"
        "///////                                            ///////\n"
        "/////// 1. A live cell with fewer than 2           ///////\n"
        "///////    live neighbors dies (underpopulation).  ///////\n"
        "///////                                            ///////\n"
        "/////// 2. A live cell with 2 or 3                 ///////\n"
        "///////    live neighbors survives.                ///////\n"
        "///////                                            ///////\n"
        "/////// 3. A live cell with more than 3            ///////\n"
        "///////    live neighbors dies (overpopulation).   ///////\n"
        "///////                                            ///////\n"
        "/////// 4. A dead cell with exactly 3              ///////\n"
        "///////    live neighbors becomes alive            ///////\n"
        "///////    (reproduction).                         ///////\n"
        "///////                                            ///////\n"
        "///////                SIMPLE TERMS:               ///////\n"
        "///////                                            ///////\n"
        "///////    0 -> 3 live neighbors -> 1 (born)       ///////\n"
        "///////    1 -> <2 or >3 live neighbors -> 0 (dies)///////\n"
        "///////                                            ///////\n"
        "////////////////////////////////////////////////////////\n"
    );

    //Create the 2d array
    grid = create_2d_array();

    min = 0;
    max = 1;
    
    //Accurate for loop for always accessing the grid
    for_LOOPS(0, row, col, grid = rand() % (max - min + 1) + min);
    //Initially, make the grid have 1s or 0s (as described by the)
    //game since everything is either alive or dead hence it is rand


    //Render the grid
    render_grid(grid);

}

void for_LOOPS(int start, int end1, int end2, int expr) {

    for (i = start; i < end1; i++) {
        for (j = start; j < end2; j++) {
            expr;
        }
    }
}

//Initialization function
char *create_2d_array() {
    //Create a fixed 2D array
    //Challenge: Make this dynamically grow with user's input
    int two_dee_array[row][col];
    return two_dee_array;
}

//Rendering Function
void render_grid(char **grid) {
    for (i = 0; i < row; i++) {
        for (j = 0; i < col; j++) {
            
        }
    }
}

int count_neighbors() {
    
}