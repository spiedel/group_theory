// analytical_fill_1.cpp

// this function will take in a grid with initial boundary conditions for problem 2
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
  inFile.open("program/conditions1.txt"); // open file
  if (!inFile){ cout << "Unable to open file \n"; exit(1);} // if the file can't be opened

  // variables for getting numbers from file
  float a;
  string line;

  getline(inFile,line); //first line not needed

  // variables for getting info
  float data[6] = {1,0,0,0,0,0}; 
  float info[3] = {0,0,0}; // empty array to store relevant info, 0:a, 1:d, 2:V.
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

      // assuming centered around origin
      if (j==0){
	      info[0]=data[1];
      }
      else if (j==1){
	      info[1]=abs(data[1]);
	      info[2]=data[5];
      }
      j=j+1;
    }
  }
  
  // filling in potential using analytical solution
  
  for (int n=0; n<nx; n++){ // itterate over x-values
    float x = dx*((float)n - ((float)nx-1)*0.5); // x = n*dx - (1/2)*dx*(nx-1)      (nx-1) in order to include 0.

    
    for (int m=0; m<ny; m++){ // itterate over y-values
      float y = dy*((float)m - ((float)ny-1)*0.5);
      
      //centre circle
      if (0 <= sqrt(pow(x,2) + pow(y,2)) && sqrt(pow(x,2) + pow(y,2)) <= (info[0]+dx/2)){
	      grid[n][m] = 0;
      }

      //positive line
      else if ( x < -info[1]+dx && x > -info[1]-dx ){
            grid[n][m]=info[2];
      }
      ///negative line
      else if ( x < info[1]+dx && x > info[1]-dx ){
            grid[n][m]=-info[2];
      }
      else {
	      float r = sqrt(pow(x,2)+pow(y,2));
	      float theta = atan2(y,x);
            //I removed a factor of 1.5 here?
	          grid[n][m] = -((info[2])/info[1])*(r)*cos(theta)*(1-(2*pow(info[0],2))/(pow(r,2)+pow(info[0],2)));
	
      }
    }
  }
  
  return grid;
}