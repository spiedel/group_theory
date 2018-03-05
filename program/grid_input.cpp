// grid_input.cpp
// this function will fill the grid with information from the given file

// header files
#include "ExampleGrid.h"
#include "header.h"

// other stuff to be included
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <math.h>

using namespace std;

// Function
Grid grid_input(char fileName[]){
   
  // Read from file
  ifstream inFile;
  inFile.open(fileName); // open file
  if (!inFile){ cout << "Unable to open file \n"; exit(1);} // if the file can't be opened

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

  // initialise grid
  Grid foo (nx,ny,dx,dy);
  
  // fill grid with NAN
  for (int i=0; i<nx; i++){
    for (int j=0; j<ny; j++){
      foo[j][i] = NAN; // yes, j and i are switched
    }
  }

  // Read through rest of file
  while (! inFile.eof() ){ // until the end of the file
    getline(inFile,line); // get each line from the file
    
    stringstream ss(line); // put the line segments into strings
    
    while (ss >> a){ // if the strings can be put into the float
      if ( a== 1 ){ // if it's a circle
	//------------------ CIRCLE -------------------------------------------------------
	float data[5] = { 1,0,0,0,0 }; // empty array to contain info about circle
	int i=1; // itteration variable
	
	while (ss >> a){ // continue to look through line for numbers
	  data[i] = a; // put data into array
	  i = i +1;
	}
	
	// Put data into grid
	for (int n=0; n<nx; n++){ // itterate over x-values
	  float x = dx*((float)n - ((float)nx-1)*0.5); // x = n*dx - (1/2)*dx*(nx-1)      (nx-1) in order to include 0.
	  
	  for (int m=0; m<ny; m++){ // itterate over y-values
	    float y = dy*((float)m - ((float)ny-1)*0.5);

	    if ( pow(data[1]-dx/2,2) <=  pow((x - data[2]),2) + pow((y - data[3]),2) && pow(data[1]+dx/2,2) >=  pow((x - data[2]),2) + pow((y - data[3]),2)  ){ // if   (r-dr)^2 <= (x-x_0)^2 + (y-y_0)^2 <= (r+dr)^2
	      // this will give a width to the circle and gives a bit of room for approximation.
	      // here dr = dx/2, it can easily be changed

	      foo[m][n] = data[4]; // put value for potential into relevant grid-elements
	    }
	  }
	}
      }
      else if (a == 2){
	//---------------------- LINE -----------------------------
	float data[6] = { 2,0,0,0,0,0 }; // empty array to contain info on line
	int i = 1; // itterator

	while ( ss >> a ){ // continue to look through line for numbers;
	  data[i] = a; // put data into array
	  i = i +1;
	}

	// minimum and maximum x and y values
	float x_min, x_max, y_min, y_max;
	
	if ( data[1] <= data[3] ){ // if x_0 < x_n
	  x_min = data[1];
	  x_max = data[3];
	}
	else { // if x_n < x_0
	  x_min = data[3];
	  x_max = data[1];
	}
	if ( data[2] <= data[4] ){ // if y_0 < y_n
	  y_min = data[2];
	  y_max = data[4];
	}
	else { // if y_n < y_0
	  y_min = data[4];
	  y_max = data[2];
	}
	
	// Put data into grid
	for (int n=0; n<nx; n++){ // itterate over x and y values / over grid elements
	  float y = dx*((float)n - ((float)nx-1)*0.5); // dx and dy are somehow messed up but this works
	  //cout << "y= " << y << "\n";
	  
	  for (int m=0; m<ny; m++){
	    float x = dy*((float)m - ((float)ny-1)*0.5);
	    //cout << "x= " << x << "\n";

	    if ( data[1] == data[3] ){ // if we have constant x-value
	      if ( x >= data[1] - dx/2 && x <= data[1] + dx/2 ){ // for x within range
		if ( y >= y_min - dy/2 && y <= y_max + dy/2 ) { // y_min < y < y_max
		  foo[m][n] = data[5]; // put potential value into relevant grid-elements
		}
	      }
	    }
	    else if ( data[2] == data[4] ){ // if we have constant y-value
	      if ( y>= -data[2] - dy/2 && y <= -data[2] + dy/2 ){ // within y range, the grid is flipped so the - sign is necessary
		if ( x >= x_min -dx/2 && x <= x_max + dx/2) { // x_min < x < x_max
		  foo[m][n] = data[5]; // put potential value into relevant grid-elements
		}
	      }
	    }
	    else { // if it's a straight line		
	      if ( y + data[2] >= ((-data[4] + data[2])/(data[3] - data[1]))*(x - data[1]) - dy/2 && y + data[2] <= ((-data[4] + data[2])/(data[3] - data[1]))*(x - data[1]) + dy/2 ){ // equation for straight line using points
	       
		if ( x >= x_min - dx/2 && x <= x_max + dx/2) { // between x-values
		  if ( y >= y_min - dy/2 && y <= y_max + dy/2 ){ // between y-values
		    foo[m][n] = data[5]; // put potential value into relevant grid-elements.
		  }
		}
	      } 
	    }
	  }
	}  
      }
      else if ( a == 3 ){
       //---------------------- RECTANGLE -----------------------------
	float data[6] = { 3,0,0,0,0,0 }; // empty array to store info on rectangle
	int i = 1; // iterator

	while ( ss >> a ){ // continue to look through line for numbers;
	  data[i] = a; // put data into array
	  i = i +1;
	}

	// Put data into grid
	for (int n=0; n<nx; n++){ // loop over x and y values / over grid elements
	  float y = dx*((float)n - ((float)nx-1)*0.5); // dx and dy are somehow messed up but this works

	  for (int m=0; m<ny; m++){
	    float x = dy*((float)m - ((float)ny-1)*0.5);

	    if ( y>= -data[2]-dx/2 && y<= -data[2]+dx/2) { // for upper horizontal side
	      if (x >= data[1]-dx/2 && x <= (data[1] + data[3]+dx/2) ){ // for some reason it did not like it if these were in the previous line
		foo[m][n] = data[5]; // put potential into relevant grid-elements
	      }
	    }
	    else if ( y>= -data[2]+data[4]-dx/2 && y<= -data[2]+data[4]+dx/2 ){ // for upper horizontal side
	      if (x >= data[1]-dx/2 && x <= (data[1] + data[3]+dx/2) ){ 
		foo[m][n] = data[5];
	      }
	    }
	    else if ( x>= data[1]-dx/2 && x<= data[1]+dx/2 ){// for left-most vertical side
	      if ( y>= -data[2]-dx/2 && y <= -(data[2] - data[4])+dx/2 ){
	      foo[m][n] = data[5];
	      
	      }
	    }
	    else if ( x>= (data[1]+data[3]-dx/2) && x<= (data[1]+data[3]+dx/2) ){// for right-most vertical side
	      if ( y>= -data[2]-dx/2 && y <= -(data[2] - data[4])+dx/2 ){
	      foo[m][n] = data[5];
	      }
	    }
	  }
	}	  
      }
      else if (a==4){ // if it's point
	// ------------------- POINT -----------------------
	float data[4] = { 4,0,0,0 }; // empty array to contain info about circle
	int i=1; // itteration variable
	
	while (ss >> a){ // continue to look through line for numbers
	  data[i] = a; // put data into array
	  i = i +1;
	}
	
	// Put data into grid
	for (int n=0; n<nx; n++){ // itterate over x-values
	  float x = dx*((float)n - ((float)nx-1)*0.5); // x = n*dx - (1/2)*dx*(nx-1)      (nx-1) in order to include 0.
	  
	  for (int m=0; m<ny; m++){ // itterate over y-values
	    float y = dy*((float)m - ((float)ny-1)*0.5);
	    
	    if ( x >= -data[1]-dx/2 && x <= -data[1]+dx/2){ // getting coordinate system right
	      if ( y >= data[2]-dy/2 && y <= data[2]+dx/2){
		foo[m][n] = data[3];
	      }
	    }
	  }
	}
      }
    }
  }
  inFile.close(); // close file
  
  return foo;
}
