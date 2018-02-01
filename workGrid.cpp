#include "ExampleGrid.h"
#include <iostream>

using namespace std;

int main(){
  int nx = 4; int ny = 6; int dx = 0.2; int dy = 0.2;
  Grid foo (nx,ny,dx,dy);

  foo[1][1]=1;
  
  cout << "It's working? \n";
  cout << "the value is: " << foo[1][1] << "\n";

  for (int i=0; i<nx; i++){
    for (int j=0; j<ny; j++){
      cout << foo[j][i] << " ";
    }
    cout << "\n";
  }
  cout << "\n";

  return 0;
}
