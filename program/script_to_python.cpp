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
#include <string>

using namespace std;

Grid plotBoundary(string fileName){
  int nx = 40; int ny = 40; float dx = 0.1; float dy = 0.1; // initialising values for grid
  //char fileName[] = "conditions1.txt"; // file for getting boundary conditions
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  grid = grid_input(nx,ny,dx,dy,fileName); // filling grid with info from

  return grid;
}