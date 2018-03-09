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
Grid numerical_solution(Grid grid, int n_max, double tolerance){
  //timer
  clock_t tStart = clock();

  // Variables  
  int nx = grid.nX(), ny = grid.nY();
  double dx = grid.dX(), dy = grid.dY();
  Grid grid_before(nx,ny,dx,dy), grid_after(nx,ny,dx,dy); // grid to contain the intial boundary conditions, grid for n and n+1.

  // grid with initial boundary conditions
  for ( int j=0; j < ny; j++ ){
    for ( int k=0; k < nx; k++ ){
      grid_before[j][k] = grid[j][k];
      
      if ( std::isnan(grid_before[j][k]) ){
	      grid_before[j][k]=0;
      }
    }
  }

  grid_after = grid_before;

  float lambda=0.0; // over-relaxation constant
  int kAfter,kBefore,jAfter,jBefore, n=0;
  double err, err_max = 1, current_grid_value;

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

	        // if there is no initial boundary condition, fill in grid using equation
	        grid_after[j][k]=grid_before[j][k] +(lambda+1)*((0.25)*(grid_before[jAfter][k]+grid_before[jBefore][k] + grid_before[j][kAfter]+grid_before[j][kBefore]) - grid_before[j][k]);
         
          err = grid_after[j][k] - grid_before[j][k];
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

// float diff, maxDiff = 0.;
//   for ( int j=0; j < ny; j++ ){
//     for ( int k=0; k < nx; k++ ){
//       if ( ! std::isnan(grid_before[j][k]) ) {
//         diff = grid_before[j][k] - grid_after[j][k];
//         if (diff < 0) {
//           diff = -diff;
//         }

//         if (diff > maxDiff) {
//           maxDiff = diff;
//         }
//       }
//     }
//   }

  cout << "Number of iterations needed: " << n << endl;
  printf("Maximum difference is: %.6f\n", err_max);
  //print time taken
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  return grid_after;
}
  
  
