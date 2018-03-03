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
  int nx = 80; int ny = 80; float dx = 0.4; float dy = 0.4; // initialising values for grid
  char fileName[] = "program/conditions4.txt"; // file for getting boundary conditions
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  Grid grid2(nx,ny,dx,dy);
  grid = grid_input(nx,ny,dx,dy,fileName); // filling grid with info from file
  grid2 = analytical_fill_2(nx,ny,dx,dy,grid);

  // flag used to 
  if (flag == 0) {
    return grid;
  }
  else {
    return grid2;
  }

}
