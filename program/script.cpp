// main script for solving everything

// header files
#include "ExampleGrid.h"
#include "header.h"

using namespace std;

<<<<<<< HEAD
int main(){
  char fileName[] = "conditions.txt"; // file for getting boundary conditions
  // Read from file
  ifstream inFile;
  inFile.open(fileName); // open file
  if (!inFile){ cout << "Unable to open file \n"; exit(1);} // if the file can't be opened
  
  // initialising values for grid
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
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  grid = grid_input(fileName); // filling grid with info from file
>>>>>>> Sofie

  if (flag == 0) {
    return grid;
  }
  else {
    return grid;
=======
/* Function to plot the boundary conditions 
* or fill in the analytical solution if the correct flag is used
* Change fileName to use different conditions
* change analytical_fill_2 to use a different solution */

Grid plotBoundary(int flag = 0){
  int nx = 100; int ny = 100; float dx = 0.2; float dy = 0.2; // initialising values for grid
  char fileName[] = "program/conditions2.txt"; // file for getting boundary conditions
  
  Grid grid(nx,ny,dx,dy); // initialising grid
  Grid grid2(nx,ny,dx,dy);
  grid = grid_input(nx,ny,dx,dy,fileName); // filling grid with info from file
  if (flag == 1) { 
    grid2 = analytical_fill_2(nx,ny,dx,dy,grid);
    return grid2;
>>>>>>> Leah_Branch
  }

  return grid;

}
