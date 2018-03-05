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
  Grid grid_0(nx,ny,dx,dy), grid_1(nx,ny,dx,dy), grid_2(nx,ny,dx,dy); // grid to contain the intial boundary conditions, grid for n and n+1.  
  float per[nx][ny];
  
  // grid with initial boundary conditions
  for ( int j=0; j < ny; j++ ){
    for ( int k=0; k < nx; k++ ){
      grid_0[j][k] = grid[j][k];
      grid_1[j][k] = grid_0[j][k];
      grid_2[j][k] = grid_0[j][k];
      per[j][k]=0;

      if ( std::isnan(grid_1[j][k]) ){
	      grid_1[j][k]=0;
        per[j][k] = 100;
      }
    }
  }

  float lambda=0.0; // over-relaxation constant
  int n_max = 5000; // maximum number of iterations.
  int kPlus,kMinus,jPlus,jMinus;
  bool flag=false;
  for (int n=0; n<n_max; n++) {
    flag = false;
    // iteration over y
    for ( int j=0; j < ny; j++ ){
      // iteration over x
      for ( int k=0; k < nx; k++ ){
	      if ( std::isnan(grid_0[j][k]) && per[j][k] >= 20) {

          flag = true;
	        kMinus = k-1;
          jMinus = j-1;
          kPlus = k+1;
          jPlus = j+1;

          //upates values if out of range
          if (kMinus<0) {
            kMinus = k+1;
          }
          if (jMinus<0) {
            jMinus = j+1;
          }
          if (kPlus>nx) {
            kPlus = k-1;
          }
          if (jPlus>ny) {
            jPlus = j-1;
          }

	        // if there is no initial boundary condition, fill in grid using equation
	        grid_2[j][k]=grid_1[j][k] +(lambda+1)*( (0.25)*(grid_1[jPlus][k]+grid_1[jMinus][k] + grid_1[j][kPlus]+grid_1[j][kMinus]) - grid_1[j][k]);
          /*if (grid_2[j][k] != 0) {         
            per[j][k] = 100. * (grid_1[j][k] + grid_2[j][k]) / grid_2[j][k];
            if (per[j][k] < 0) {
              per[j][k] = - per[j][k];
            }
          }*/
	      }
      }
    }
    // update grid_1 to be grid_2 for next iteration
    for ( int j=0; j < ny; j++ ){
      for ( int k=0; k < nx; k++ ){
	      grid_1[j][k] = grid_2[j][k];
      }
    }
    if ( flag == false ) {
      break;
    }
  }

  if (flag == true) {
    cout << "look " << flag;
  }
  //print time taken
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  return grid_1;
}
  
  
