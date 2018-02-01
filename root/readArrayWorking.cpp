#include "ExampleGrid.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int workGrid(){
  int nx = 10; int ny = 15; double dx = 0.1; double dy = 0.2;
  double xmax=nx*dx, ymax=ny*dy;
  Grid foo(nx,ny,dx,dy);
  

  //make sure variables are clear
  delete gROOT->FindObject("histo");

  //initialise random numbers
  srand(time(NULL));

  //fill foo with random numbers
  for (int i=0; i<nx; i++){
    for (int j=0; j<ny; j++){
      foo[i][j] = 20*double(rand())/RAND_MAX;
      cout << foo[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";

  TH2* histo = new TH2D("histo", "Histogram from array;x;y",
			nx,0,xmax,
			ny,0,ymax);

  for (int i=0; i<nx; i++) {
    for (int j=0; j<ny; j++) {
      histo->Fill(double(i)*(xmax)/nx,
 		  double(j)*(ymax)/ny,
 		  foo[i][j]);
    }
  }

  TCanvas * c = new TCanvas("c", "Canvas", 800, 800);
  histo->Draw("Colz");
  c->Update();
  
  return 0;
}
