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
Grid SOR(Grid grid, int n_max, double tolerance){
  //timer
  clock_t tStart = clock();

  // Variables
  //grids to contain the solution and the second to last iteration
  int nx = grid.nX(), ny = grid.nY();
  double dx = grid.dX(), dy = grid.dY(), omega=1.9;
  double beta = dx/dy, denom = 2*(1+beta*beta);
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
  double err, err_max = 1, current_grid_value;

  while (err_max > tolerance && n < n_max) {

    grid_second_last_iteration = grid_solution;

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
	        grid_solution[j][k]=0.25*omega*(grid_solution[jAfter][k]+grid_solution[jBefore][k] 
                  + grid_solution[j][kAfter]+grid_solution[j][kBefore]) + (1-omega)*grid_solution[j][k];
         
          err = abs(current_grid_value - grid_solution[j][k]);
          if ( err > err_max ) {
            err_max = err;
          }

          //leah equation
          //solution[i][j] = (intermediate[iMinus][j]+intermediate[iPlus][j]+
          //beta*beta*(solution[i][jMinus]+intermediate[i][jPlus]))/
          //(2*(1+beta*beta));
        }
      }
    }
  }

float diff, maxDiff = 0.;
  for ( int j=0; j < ny; j++ ){
    for ( int k=0; k < nx; k++ ){
      if ( ! std::isnan(grid_solution[j][k]) ) {
        diff = grid_solution[j][k] - grid_second_last_iteration[j][k];
        if (diff < 0) {
          diff = -diff;
        }

        if (diff > maxDiff) {
          maxDiff = diff;
        }
      }
    }
  }

  printf("Maximum difference is: %.6f\n", maxDiff);
  //print time taken
  cout << "Number of iterations needed: " << n << endl;
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  return grid_solution;
}
  
  
