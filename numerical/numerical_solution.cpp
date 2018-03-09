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
Grid numerical_solution(int nx, int ny, float dx, float dy, Grid grid){
  //timer
  clock_t tStart = clock();

  // Variables
  Grid grid_boundary(nx,ny,dx,dy), grid_before(nx,ny,dx,dy), grid_after(nx,ny,dx,dy); // grid to contain the intial boundary conditions, grid for n and n+1.  

  
  // grid with initial boundary conditions
  for ( int j=0; j < ny; j++ ){
    for ( int k=0; k < nx; k++ ){
      grid_boundary[j][k] = grid[j][k];
      grid_before[j][k] = grid_boundary[j][k];
      
      if ( std::isnan(grid_before[j][k]) ){
	      grid_before[j][k]=0;
      }
    }
  }

  grid_after = grid_before;

  float lambda=0.0; // over-relaxation constant
  int n_max = 5000; // maximum number of iterations.
  int kAfter,kBefore,jAfter,jBefore, n;
  
  for (n=0; n<n_max; n++) {
    // iteration over y
    for ( int j=0; j<nx; j++ ){
      // iteration over x
      for ( int k=0; k<ny; k++ ){
	      if ( std::isnan(grid_boundary[j][k]) ) {

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
	        //grid_after[j][k]=grid_before[j][k] +(lambda+1)*((0.25)*(grid_before[jAfter][k]+grid_before[jBefore][k] + grid_before[j][kAfter]+grid_before[j][kBefore]) - grid_before[j][k]);
          grid_after[j][k]=0.25*(grid_before[jAfter][k] + grid_before[jBefore][k] +
                             grid_before[j][kAfter] + grid_before[j][kBefore]);
         
         
          //leah equation
          //solution[i][j] = (intermediate[iMinus][j]+intermediate[iPlus][j]+
          //beta*beta*(solution[i][jMinus]+intermediate[i][jPlus]))/
          //(2*(1+beta*beta));
        }
      }
    }

    if (n != n_max-1) {
      // update grid_before to be grid_after for next iteration
      grid_before = grid_after;
    }
  }

float diff, maxDiff = 0.;
  for ( int j=0; j < ny; j++ ){
    for ( int k=0; k < nx; k++ ){
      if ( ! std::isnan(grid_before[j][k]) ) {
        diff = grid_before[j][k] - grid_after[j][k];
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
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  return grid_after;
}
  
  
