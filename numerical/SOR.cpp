// numerical_solution.cpp

// this function will take in a grid with initial boundary conditions and calculate a numerical solution

// header files
#include "ExampleGrid.h"
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
//omega is the relaxation constant 
Grid SOR(Grid grid, int n_max, double tolerance, double omega=1.9){
  //timer
  clock_t tStart = clock();

  // Variables
  //grids to contain the solution and the second to last iteration
  int nx = grid.nX(), ny = grid.nY();
  double dx = grid.dX(), dy = grid.dY();
  Grid grid_solution(nx,ny,dx,dy), grid_second_last_iteration(nx,ny,dx,dy);  

  
  // grid with initial boundary conditions
  for ( int j=0; j < ny; j++ ){
    for ( int k=0; k < nx; k++ ){
      grid_solution[j][k] = grid[j][k];
      
      if ( std::isnan(grid_solution[j][k]) ){
	      grid_solution[j][k]=0;
      }
    }
  }

  int kAfter,kBefore,jAfter,jBefore, n=0;
  double err, err_max = 1, current_grid_value, new_grid_value;
  double beta = dx/dy, denom = 1/(2*(1+beta*beta));
  cout << beta << " " << denom << " " << omega;

  while (err_max > tolerance && n < n_max) {

    //increment iteration number and reset maximum error for this iteration
    err_max = 0;
    n++;
    
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

          current_grid_value = grid_solution[j][k];
	        // if there is no initial boundary condition, fill in grid using equation
	        new_grid_value=denom*omega*(grid_solution[jAfter][k]+grid_solution[jBefore][k] 
                  + beta*beta*(grid_solution[j][kAfter]+grid_solution[j][kBefore])) 
                  + (1-omega)*current_grid_value;
          
          grid_solution[j][k] = new_grid_value;
          
          err = abs(current_grid_value - new_grid_value);
          if ( err > err_max ) {
            err_max = err;
          }
        }
      }
    }
  }

  printf("Maximum difference is: %.6f\n", err_max);
  //print time taken
  cout << "Number of iterations needed: " << n << endl;
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  return grid_solution;
}
  
  
