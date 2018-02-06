#include "../gridExamples/ExampleGrid.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int readArrayWorking(){
  int nx = 100; int ny = 150; double dx = 0.1; double dy = 0.2;
  double xmax=20, ymax=10;
  Grid foo(nx,ny,dx,dy);

  //make pretty
  gStyle->SetPalette(kBird);
  gStyle->SetOptStat(0);

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
			nx*dx,0,xmax,
			ny*dy,0,ymax);

  for (int i=0; i<nx; i++) {
    for (int j=0; j<ny; j++) {
      histo->Fill(double(i)*(xmax)/foo.nX(),
 		  double(j)*(ymax)/foo.nY(),
 		  foo[i][j]);
    }
  }

  TCanvas * c = new TCanvas("c", "Canvas", 800, 800);
  histo->Draw("Colz");
  c->Update();

  TImage *img = TImage::Create();
  img->FromPad(c);
  char name[] = "1_cpp";
  img->WriteImage("./graphs/1_cpp.png");
  
  return 0;
}
