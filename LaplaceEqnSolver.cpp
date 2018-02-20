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
      if (! std::isnan(boundary[i][j])) {
        intermediate[i][j] = boundary[i][j];
        solution[i][j] = boundary[i][j];
      }
      else {
        intermediate[i][j]=0.;
        solution[i][j]=0.;
      }
    }
  }


  //beta is a value in eqn, tolarance is max squared error
  //maxError is largest error bewteen one 
  double beta=dx/dy, tolarence=0.0000000000001, currentErr, maxError=1;
  int n=0, iMinus, iPlus, jMinus, jPlus;

  //loop up to n times
  //not sure about tolarence - don't want too many zero values
  while (n<1000 && tolarence<maxError) {

    //set to 0 so can find maximum
    maxError = 0;

    //loop through space
    for (int i=0; i<nx; i++) {
      for (int j=0; j<ny; j++) {

        //check if a boundary value
        if (! std::isnan(boundary[i][j])) {
          solution[i][j] = boundary[i][j];
        }

        //boundary situation - this assumes that it infinitely repeats so graph[i]=graph[-i]
         else {
          //ie index i+1 doesn't exist
          iMinus = i-1;
          jMinus = j-1;
          iPlus = i+1;
          jPlus = j+1;

          //upates values if out of range
          if (iMinus<0) {
            iMinus = iMinus+2;
          }
          if (jMinus<0) {
            jMinus = jMinus+2;
          }
          if (iPlus>nx) {
            iPlus = iPlus-2;
          }
          if (jPlus>ny) {
            jPlus = jPlus-2;
          }

          solution[i][j] = (intermediate[iMinus][j]+intermediate[iPlus][j]+
          beta*beta*(intermediate[i][jMinus]+intermediate[i][jPlus]))/
          (2*(1+beta*beta));
        }

        //take square to avois issues of sign differences
        currentErr = (solution[i][j]-intermediate[i][j])*(solution[i][j]-intermediate[i][j]);
        if (maxError<currentErr) {
          maxError = sqrt(currentErr);
        }


      }

    }

    //each iteration set intermediate to next time step
    for (int i=0; i<(nx); i++) {
      for (int j=0; j<(ny); j++) {
        intermediate[i][j] = solution[i][j];
      }
    }
   
   
    n+=1;
  }

  if ( n == 1000 ) {
    cout << "Didn't reach tolarance level. Consider increasing n." << endl;
    cout << "Maximum error between iterations was: " << maxError << endl;
  }
  else {
    cout << n << endl;
  }

  for (int i=0; i<(nx); i++) {
    for (int j=0; j<(ny); j++) {
      cout << solution[i][j] << " ";
    }
    cout << endl;
  }

  return solution;
}

