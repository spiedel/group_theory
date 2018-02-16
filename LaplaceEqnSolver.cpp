//LaplaceEqnSolver.cpp

//solving the equation using the method from ocw.usu.edu/Civil_and_Enviromental_Engineering

#include "gridExamples/ExampleGrid.h"
#include "header.h"

#include<iostream>
#include<cmath>

using namespace std;

Grid solve(Grid boundary) {

  //initialise grid variables
  unsigned nx = boundary.nX();
  unsigned ny = boundary.nY();
  double dx = boundary.dX();
  double dy = boundary.dY();

  //solution is intermediate at time+1 
  Grid intermediate(nx,ny,dx,dy);
  Grid solution(nx,ny,dx,dy);

  //initialise solution with boudary values
  for (int i=0; i<nx; i++) {
    for (int j=0; j<ny; j++) {
      if (! isnan(boundary[i][j])) {
        intermediate[i][j] = boundary[i][j];
        solution[i][j]=0;
      }
      else {
        intermediate[i][j]=0;
        solution[i][j]=0;
      }
    }
  }


  //beta is a value in eqn, tolarance is max squared error
  //maxError is largest error bewteen one 
  double beta, tolarence=0.1, maxError=0.11;
  int n=0;

  while (n<100 && tolarence<maxError) {
    cout << "In while loop" << endl;
    for (int i=1; i<(nx-1); i++) {
      for (int j=1; j<(ny-1); j++) {

        //check if a boundary value
        if (! isnan(boundary[i][j])) {
          solution[i][j] = boundary[i][j];
        }
        //if not update 
        else {
          beta = dx/dy;
          //set solution to eqn value
          solution[i][j] = (intermediate[i-1][j]+intermediate[i+1][j]+
                            beta*beta*(intermediate[i][j-1]+intermediate[i][j+1]))/
                            (2*(1+beta*beta));
          cout << solution[i][j] << endl;
        }

        //take square to avois issues of sign differences
        if (maxError<(solution[i][j]-intermediate[i][j])*(solution[i][j]-intermediate[i][j])) {
          maxError = (solution[i][j]-intermediate[i][j])*(solution[i][j]-intermediate[i][j]);
        }


      }

    }

    //each iteration set intermediate to next time step
    for (int i=1; i<(nx-1); i++) {
      for (int j=1; j<(ny-1); j++) {
        intermediate[i][j] = solution[i][j];
      }
    }
   
   
    n+=1;
  }

  return solution;
}

