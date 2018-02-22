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

using namespace std;

int main(){
  int nx = 20; int ny = 20; float dx = 0.2; float dy = 0.2; // initialising values for grid
  char fileName[] = "conditions2.txt"; // file for getting boundary conditions
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  grid = grid_input(nx,ny,dx,dy,fileName); // filling grid with info from file

  // print out grid
  for (int i=0; i<nx; i++){ // loop over rows and columns
    for (int j=0; j<ny; j++){
      if (isnan(grid[j][i]) == 1){ // if the element is NAN then print empty space (makes it look nicer)
	cout << "  ";
      }
      else {
	cout << grid[j][i] << " ";
      }
    }
    cout << "\n";
  }
  cout << "\n";
  
  return 0;
}
