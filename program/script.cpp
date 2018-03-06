// main script for solving everything

// header files
#include "ExampleGrid.h"
#include "header.h"

using namespace std;

/* Function to plot the boundary conditions 
* or fill in the analytical solution if the correct flag is used
* Change fileName to use different conditions
* change analytical_fill_2 to use a different solution */

Grid plotBoundary(int flag = 0){
  int nx = 100; int ny = 100; float dx = 0.2; float dy = 0.2; // initialising values for grid
  char fileName[] = "program/conditions2.txt"; // file for getting boundary conditions
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  Grid grid2(nx,ny,dx,dy);
  grid = grid_input(nx,ny,dx,dy,fileName); // filling grid with info from file
  if (flag == 1) { 
    grid2 = analytical_fill_2(nx,ny,dx,dy,grid);
    return grid2;
  }

  return grid;

}
