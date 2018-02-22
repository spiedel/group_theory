// main script for solving everything

// header files
#include "ExampleGrid.h"
#include "header.h"


// Other stuff to include
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <math.h>
#include <iomanip> // for precision when printing

using namespace std;

Grid plotBoundary(int flag = 0){
  int nx = 50; int ny = 50; float dx = 0.4; float dy = 0.4; // initialising values for grid
  char fileName[] = "program/conditions2.txt"; // file for getting boundary conditions
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  Grid grid2(nx,ny,dx,dy);
  grid = grid_input(nx,ny,dx,dy,fileName); // filling grid with info from file
  grid2 = analytical_fill_2(nx,ny,dx,dy,grid);

  if (flag == 0) {
    return grid;
  }
  else {
    return grid2;
  }

}
