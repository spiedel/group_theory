// numerical_solution.cpp

// this function will take in a grid with initial boundary conditions and calculate a numerical solution

// header files
#include "../program/ExampleGrid.h"
// other stuff to be included
//#include <iostream> // terminal io
//#include <fstream> // file io
//#include <sstream> // strings
#include <cmath> 
#include <math.h>
#include <time.h>

using namespace std;

// Function
// grid is the boundary grid, 
//n_max is maximum number of iterations, 
//tolerance is the max difference between subsequent iterations
Grid jacobi(Grid grid, int n_max, double tolerance){
  //timer
  clock_t tStart = clock();

  // Variables  
  int nx = grid.nX(), ny = grid.nY();
  double dx = grid.dX(), dy = grid.dY();
  Grid grid_before(nx,ny,dx,dy), grid_after(nx,ny,dx,dy); // grid to contain the intial boundary conditions, grid for n and n+1.

  // fill grid with initial boundary conditions
  for ( int j=0; j < nx; j++ ){
    for ( int k=0; k < ny; k++ ){
      grid_before[j][k] = grid[j][k];
      
      if ( std::isnan(grid_before[j][k]) ){
	      grid_before[j][k]=0;
      }
    }
  }

  grid_after = grid_before;

  int kAfter,kBefore,jAfter,jBefore, n=0;
  double err, err_max = 1, current_grid_value, next_grid_value; 
  double beta=dx/dy, denom = 1/(2*(1+beta*beta));

  while (err_max > tolerance && n < n_max) {

    //increment iteration number and reset maximum error for this iteration
    err_max = 0;
    n++;
    // update grid_before to be grid_after for next iteration
    grid_before = grid_after;
    // iteration over y
    for ( int j=0; j<nx; j++ ){
      // iteration over x
      for ( int k=0; k<ny; k++ ){
	      if ( std::isnan(grid[j][k]) ) {

	        kBefore = k-1;
          jBefore = j-1;
          kAfter = k+1;
          jAfter = j+1;

          //upates values if out of range
          if (kBefore<0) {
            kBefore = k+1;
          }
          if (jBefore<0) {
            jBefore = j+1;
          }
          if (kAfter>=ny) {
            kAfter = k-1;
          }
          if (jAfter>=nx) {
            jAfter = j-1;
          }

	        current_grid_value = grid_before[j][k];
          // if there is no initial boundary condition, fill in grid using equation
	        next_grid_value=(grid_before[jAfter][k]+grid_before[jBefore][k]
                          +beta*beta*(grid_before[j][kAfter]+grid_before[j][kBefore]))*denom;
         
          grid_after[j][k]=next_grid_value;
          err = next_grid_value-current_grid_value;
          if ( err > err_max ) {
            err_max = err;
          }
        }
      }
    }
  }

  cout << "Number of iterations needed: " << n << endl;
  printf("Maximum difference is: %.6f\n", err_max);
  //print time taken
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  return grid_after;
}
  
  
