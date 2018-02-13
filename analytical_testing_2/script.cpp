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

int main(){
  int nx = 20; int ny = 20; float dx = 0.2; float dy = 0.2; // initialising values for grid
  char fileName[] = "conditions2.txt"; // file for getting boundary conditions
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  Grid grid2(nx,ny,dx,dy);
  grid = grid_input(nx,ny,dx,dy,fileName); // filling grid with info from file
  grid2 = analytical_fill_2(nx,ny,dx,dy,grid);

  
  // print out grid
  
  for (int i=0; i<nx; i++){
    for (int j=0; j<ny; j++){
      
      if (isnan(grid2[j][i]) == 1){
	cout << "      ";
      }
      
      else if (grid2[j][i] == 0){
	cout << "0.000 ";
      }
      else if (grid2[j][i] == 2){
	cout << "2.000 ";
      }
      else if (grid2[j][i] == -2){
	cout << "-2.000 ";
      }
      else {
	cout << setprecision(3) << grid2[j][i] <<  " ";
   }
    }
    cout << "\n";
  }
  
  return 0;
}
