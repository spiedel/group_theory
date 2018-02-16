// header file with all the functions
#include "ExampleGrid.h"

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

Grid grid_input(int nx, int ny, float dx, float dy, char fileName[]);

#endif

#ifndef NUMERICAL_H_INCLUDED
#define NUMERICAL_H_INCLUDED

Grid numerical_solution(int nx, int ny, float dx, float dy, Grid grid);

#endif
