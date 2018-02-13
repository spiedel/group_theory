// analytical_fill_1.cpp

// this function will take in a grid with initial boundary conditions for problem 1
// it will then fill in the rest of the grid with appropriate values given by the analytical solution

// header files
#include "ExampleGrid.h"
#include "header.h"

// other stuff to be included
#include <iostream> // terminal io
#include <fstream> // file io
#include <sstream> // strings
#include <cmath> 
#include <math.h>

using namespace std;

// Function
Grid analytical_fill_1(int nx, int ny, float dx, float dy, Grid grid){
  // Read from file
  ifstream inFile;
  inFile.open("conditions1.txt"); // open file
  if (!inFile){ cout << "Unable to open file \n"; exit(1);} // if the file can't be opened

  // variables for getting numbers from file
  float a;
  string line;

  // variables for getting info
  float data[5] = { 1,0,0,0,0 }; // empty array to contain info about circle
  float radii[2] = {0,0}; // empty array with radii
  float potentials[2] = {0,0}; // empty array with potentials
  int j=0; // itteration variable 

  // reading through file
  while (! inFile.eof() ){ // until the end of the file
    getline(inFile,line); // get each line from the fileb
    
    stringstream ss(line); // put the line segments into strings
    
    while (ss >> a){ // if the strings can be put into the float
      int i=1; // itteration variable
      
      while (ss >> a){ // continue to look through line for number
	data[i] = a; // put data into array
	i = i +1;
      }
      
      radii[j] = data[1];
      potentials[j] = data[4];
      j = j+1; 
    }
  }
  
  // filling in potential using analytical solution  
  for (int n=0; n<nx; n++){ // itterate over x-values
    float x = dx*((float)n - ((float)nx-1)*0.5); // x = n*dx - (1/2)*dx*(nx-1)      (nx-1) in order to include 0.
    
    for (int m=0; m<ny; m++){ // itterate over y-values
      float y = dy*((float)m - ((float)ny-1)*0.5);
      
      if (0 <= sqrt(pow(x,2) + pow(y,2)) && sqrt(pow(x,2) + pow(y,2)) <= (radii[0]+dx/2)){
	grid[m][n] = potentials[0];
      }
      else if (radii[0] < sqrt(pow(x,2) + pow(y,2)) && sqrt(pow(x,2) + pow(y,2)) < radii[1]){
	grid[m][n] = potentials[1]* ( (log(sqrt(pow(x,2) + pow(y,2))) - log(radii[0]) )/( log(radii[1]) - log(radii[0]) ) );
      }
      if ( (radii[1]-dx/2) <= sqrt(pow(x,2) + pow(y,2)) && (radii[1]+dx/2) >= sqrt(pow(x,2) + pow(y,2)) ){
	grid[m][n] = potentials[1];
      }
    }
  }
  cout << "\n \n";
  
  return grid;
}
