// numerical_solution.cpp

// this function will take in a grid with initial boundary conditions and calculate a numerical solution

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
Grid numerical_solution(int nx, int ny, float dx, float dy, Grid grid){
  // Variables
  Grid grid_0(nx,ny,dx,dy), grid_1(nx,ny,dx,dy), grid_2(nx,ny,dx,dy); // grid to contain the intial boundary conditions, grid for n and n+1.
  // grid with initial boundary conditions
  for ( int j=0; j < ny; j++ ){
    for ( int k=0; k < nx; k++ ){
      grid_0[j][k] = grid[j][k];
      grid_1[j][k] = grid_0[j][k];

      if ( isnan(grid_1[j][k])==1 ){
	grid_1[j][k]=0;
      }
    }
  }

  float lambda=0.0; // over-relaxation constant
  int n_max = 500; // maximum number of iterations.

  for ( int n=1; n < n_max; n++ ){
    // iteration over y
    for ( int j=1; j < ny-1; j++ ){
      // iteration over x
      for ( int k=1; k < nx-1; k++ ){
	if ( isnan(grid_0[j][k]) == 1 ){
	  // if there is no initial boundary condition, fill in grid using equation
	  grid_2[j][k]=grid_1[j][k] +(lambda+1)*( (0.25)*(grid_1[j+1][k]+grid_1[j-1][k] + grid_1[j][k+1]+grid_1[j][k-1]) - grid_1[j][k]);
	}
	else {
	  // there is an initial boundary condition, fill the grid with this condition
	  grid_2[j][k]=grid_0[j][k];
	}
      }
    }
    // update grid_1 to be grid_2 for next iteration
    for ( int j=0; j < ny; j++ ){
      for ( int k=0; k < nx; k++ ){
	grid_1[j][k] = grid_2[j][k];
      }
    }
  }
  
  return grid_1;
}
  
  
