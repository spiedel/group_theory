// main script for solving everything
#include "ExampleGrid.h"
#include "header.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <math.h>

using namespace std;

int main(){
  int nx = 40; int ny = 40; float dx = 0.1; float dy = 0.1;
  Grid stuff (nx,ny,dx,dy);
  stuff = grid_input(nx,ny,dx,dy);

  // print out grid
  for (int i=0; i<nx; i++){
    for (int j=0; j<ny; j++){
      if (isnan(stuff[j][i]) == 1){
	cout << "  ";
      }
      else {
	cout << stuff[j][i] << " ";
      }
    }
    cout << "\n";
  }
  cout << "\n";
  
  return 0;
}
