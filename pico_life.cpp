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
                pico_unicorn.set_pixel(col, row, 0, 0, 0);
            }
        }
    }
}

/**
 * Copies one array into another - probably a better more C++y way of doing this
 */
void copyGrid (bool grid[GRID_HEIGHT][GRID_WIDTH], bool grid2[GRID_HEIGHT][GRID_WIDTH])
{
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

void generateRandomGrid(bool grid[GRID_HEIGHT][GRID_WIDTH], int threshold = 8)
{
    for(int row=0;row<GRID_HEIGHT;row++) {
        for(int col=0;col<GRID_WIDTH;col++) {
            int key = rand() % 10;
            if(key > threshold) {
                grid[row][col] = 1;
            } else {
                grid[row][col] = 0;
            }
        }
    }
}

int main()
{
    int threshold = 8;

    srand(time(0));
    pico_unicorn.init();

    bool grid[GRID_HEIGHT][GRID_WIDTH] = {};

    for(int row=0;row<GRID_HEIGHT;row++) {
        for(int col=0;col<GRID_WIDTH;col++) {
            int key = rand() % 10;
            if(key > threshold) {
                grid[row][col] = 1;
            } else {
                grid[row][col] = 0;
            }
        }
    }

    pico_unicorn.clear();

    while(1) {
        if(pico_unicorn.is_pressed(pico_unicorn.A)) {
            pico_unicorn.clear();
            generateRandomGrid(grid, threshold);
        }

        if(pico_unicorn.is_pressed(pico_unicorn.X)) {
            pico_unicorn.clear();
            threshold++;
            if(threshold>10) {
                threshold = 10;
            }

            generateRandomGrid(grid, threshold);
        }

        if(pico_unicorn.is_pressed(pico_unicorn.Y)) {
            pico_unicorn.clear();
            threshold--;
            if(threshold<1) {
                threshold = 1;
            }
            
            generateRandomGrid(grid, threshold);
        }

        displayGrid(grid);
        nextGeneration(grid);
        sleep_ms(120);
    }

    return 0;
}