// header file with all the functions
#include "ExampleGrid.h"

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

Grid grid_input(int nx, int ny, float dx, float dy, char fileName[]);

#endif

#ifndef ANALYTICAL_H_INCLUDED
#define ANALYTICAL_H_INCLUDED

Grid analytical_fill_1(int nx, int ny, float dx, float dy, Grid grid);

#endif
