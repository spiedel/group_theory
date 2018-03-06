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
  char fileName[] = "conditions.txt"; // file for getting boundary conditions
  // Read from file
  ifstream inFile;
  inFile.open(fileName); // open file
  if (!inFile){ cout << "Unable to open file \n"; exit(1);} // if the file can't be opened
  
  // initialising values for grid
  // variables for getting numbers
  float a, NX, NY, dx, dy;
  string line;
  int q=0;
  
  getline(inFile,line); // get line from file
  stringstream ss(line);

  while (ss >> a){
    if (q==0){
      NX=a;
    }
    else if (q==1){
      dx=a;
    }
    else if (q==2){
      NY=a;
    }
    else if (q==3){
      dy=a;
    }
    q = q+1;
  }
  
  float nx = (2*NX+1)/dx;
  float ny = (2*NY+1)/dy;
  
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
