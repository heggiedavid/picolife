/**
 * unicorn_blink
 * 
 * modified into a simple game of life implementation
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico_unicorn.hpp"

using namespace pimoroni;

PicoUnicorn pico_unicorn;

const int GRID_HEIGHT = 7;
const int GRID_WIDTH = 16;

/**
 * display the grid on the pico unicorn in random pretty colours
 */
void displayGrid(bool grid[GRID_HEIGHT][GRID_WIDTH])
{
    for(int row=0;row<GRID_HEIGHT;row++) {
        for(int col=0;col<GRID_WIDTH;col++) {
            if(grid[row][col]) {
                pico_unicorn.set_pixel(col, row, rand() % 100 + 55, rand() % 100 + 55, rand() % 100 + 55);
            } else {
                pico_unicorn.set_pixel(col, row, 0,0,0);
            }
        }
    }
}

/**
 * Copies one array into another - probably a better more C++y way of doing this
 */
void copyGrid (bool grid[GRID_HEIGHT][GRID_WIDTH],bool grid2[GRID_HEIGHT][GRID_WIDTH]) {
    for(int row=0;row<GRID_HEIGHT;row++) {
        for(int col=0;col<GRID_WIDTH;col++) {
            grid2[row][col] = grid[row][col];
        }
    }
}

/**
 * nextGeneration(grid)
 * 
 * updates the grid array with the next generation, based on the rules
 * 
 * copies grid -> grid2 array; runs rules on grid2 and updates grid1
 */
void nextGeneration(bool grid[GRID_HEIGHT][GRID_WIDTH]) {
    bool grid2[GRID_HEIGHT][GRID_WIDTH] = {};
    copyGrid(grid, grid2);

    for(int row=0;row<GRID_HEIGHT;row++) {
        for(int col=0;col<GRID_WIDTH;col++) {
            
            // get live neighbours
            int livingNeighbours = 0;
            for(int i=-1;i<2;i++) {
                for(int j=-1;j<2;j++) {
                    if(!(i == 0 && j == 0)) {
                        if(grid2[row+i][col+j]) {
                            ++livingNeighbours;
                        }
                    }
                }
            }

            // update grid from rules
            if(livingNeighbours < 2) {
                grid[row][col] = false;
            } else if(livingNeighbours == 3) {
                grid[row][col] = true;
            } else if(livingNeighbours > 3) {
                grid[row][col] = false;
            }
        }
    }
}

int main()
{
    srand(time(0));
    pico_unicorn.init();

    bool grid[GRID_HEIGHT][GRID_WIDTH] = {};

    // Randomly generate starting grid - configurable percentage of living:dead
    for(int row=0;row<GRID_HEIGHT;row++) {
        for(int col=0;col<GRID_WIDTH;col++) {
            int key = rand() % 10;
            if(key > 8) {
                grid[row][col] = 1;
            } else {
                grid[row][col] = 0;
            }
        }
    }

    pico_unicorn.clear();

    while(1) {
        displayGrid(grid);
        nextGeneration(grid);
        sleep_ms(120);
    }

    return 0;
}