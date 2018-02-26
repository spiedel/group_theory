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
  float nx = (2*1+1)/0.1; float ny = (2*1+1)/0.1; float dx = 0.1; float dy = 0.1; // initialising values for grid
  char fileName[] = "conditions4.txt"; // file for getting boundary conditions
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  grid = grid_input(fileName); // filling grid with info from file

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
