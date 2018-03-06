// header file with all the functions
#include "ExampleGrid.h"

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

Grid grid_input(char fileName[]);

#endif

#ifndef ANALYTICAL_H_1_INCLUDED
#define ANALYTICAL_H_1_INCLUDED

Grid analytical_fill_1(int nx, int ny, float dx, float dy, Grid grid);

#endif

#ifndef ANALYTICAL_H_2_INCLUDED
#define ANALYTICAL_H_2_INCLUDED

Grid analytical_fill_2(int nx, int ny, float dx, float dy, Grid grid);

#endif