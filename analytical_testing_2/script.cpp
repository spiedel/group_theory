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

Grid plotBoundary(int flag=0){
//flag is a optional value to print analytical solution

  int nx = 20; int ny = 20; float dx = 0.2; float dy = 0.2; // initialising values for grid
  char fileName[] = "analytical_testing_2/conditions2.txt"; // file for getting boundary conditions
  
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
