#include "ExampleGrid.h"
#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <math.h>

using namespace std;

Grid grid_input(int nx, int ny, float dx, float dy){
  // initialise grid
  Grid foo (nx,ny,dx,dy);

  // print out grid
  for (int i=0; i<nx; i++){
    for (int j=0; j<ny; j++){
      foo[j][i] = NAN;
    }
  }
   
  // read from file
  ifstream inFile;
  inFile.open("conditions1.txt");
  if (!inFile){ cout << "Unable to open file \n"; exit(1);}

  // variables for getting numbers
  float a;
  string line;

  
  while (! inFile.eof() ){ // until the end of the file
    getline(inFile,line); // get each line from the file
    
    stringstream ss(line); // put the line segments into strings
    
    while (ss >> a){ // if the strings can be put into the float
          
      if ( a== 1 ){ // if it's a circle
	//------------------ CIRCLE -------------------------------------------------------
	float data[5] = { 1,0,0,0,0 };
	int i=1;
	
	while (ss >> a){ // continue to look through line for numbers
	  data[i] = a; // put data into array
	  i = i +1;
	}
	// Put data into grid
	for (int n=0; n<nx; n++){
	  float x = dx*((float)n - ((float)nx-1)*0.5);
	  
	  for (int m=0; m<ny; m++){
	    float y = dy*((float)m - ((float)ny-1)*0.5);

	    if ( pow(data[1]-dx/2,2) <=  pow((x - data[2]),2) + pow((y - data[3]),2) && pow(data[1]+dx/2,2) >=  pow((x - data[2]),2) + pow((y - data[3]),2)  ){
	      foo[m][n] = data[4];
	    }
	  }
	}
	for (int g=0; g<5; g++){
	  cout << data[g] << " ";
	}
	cout << "\n";
      }
      else if (a == 2){
	//---------------------- LINE -----------------------------
	float data[6] = { 2,0,0,0,0,0 };
	int i = 1;

	while ( ss >> a ){ // continue to look through line for numbers;
	  data[i] = a; // put data into array
	  i = i +1;
	}

	// Put data into grid
	for (int n=0; n<nx; n++){
	  float y = dx*((float)n - ((float)nx-1)*0.5); // dx and dy are somehow messed up but this works
	  
	  for (int m=0; m<ny; m++){
	    float x = dy*((float)m - ((float)ny-1)*0.5);
	    
	    if ( data[1] == data[3] ){ // if we have constant x-value
	      if ( x == data [1] ){ // all y-values
		foo[m][n] = data[5];
	      }
	    }
	    else if ( data[2] == data[4] ){ // if we have constant y-value
	      if ( y == -data[2] ){ // all x-values, the grid is flipped so the - sign is necessary
		foo[m][n] = data[5];
	      }
	    }
	    else {
	      if ( y + data[2] == ((-data[4] + data[2])/(data[3] - data[1]))*(x - data[1]) ){ // equation for straight line between given points
		foo[m][n] = data[5];
	      }
	    }
	  }
	}  
      }
      else if ( a == 3 ){
       //---------------------- BOX -----------------------------
	float data[6] = { 3,0,0,0,0,0 };
	int i = 1;

	while ( ss >> a ){ // continue to look through line for numbers;
	  data[i] = a; // put data into array
	  i = i +1;
	}

	// Put data into grid
	for (int n=0; n<nx; n++){
	  float y = dx*((float)n - ((float)nx-1)*0.5); // dx and dy are somehow messed up but this works
	  
	  for (int m=0; m<ny; m++){
	    float x = dy*((float)m - ((float)ny-1)*0.5);

	    if ( y == -data[2] ){ // for upper horizontal side
	      if (x >= data[1] && x <= (data[1] + data[3]) ){ // for some reason it did not like it if these were in the previous line
	      foo[m][n] = data[5];
	      }}
	    else if ( y == -data[2]+data[4] ){ // for upper horizontal side
	      if (x >= data[1] && x <= (data[1] + data[3]) ){ 
	      foo[m][n] = data[5];
	      }}
	    else if ( x == data[1] ){// for left-most vertical side
	      if ( y>= -data[2]&& y <= -(data[2] - data[4]) ){
	      foo[m][n] = data[5];
	    }}
	    else if ( x == (data[1]+data[3]) ){// for left-most vertical side
	      if ( y>= -data[2]&& y <= -(data[2] - data[4]) ){
	      foo[m][n] = data[5];
	    }}
	  }
	}	  
      }			 
    }
  }
  inFile.close();
  
  return foo;
}
