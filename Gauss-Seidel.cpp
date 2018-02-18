#include <iostream>
#include "gridExamples/ExampleGrid.h"
#include <iomanip>
#include <cmath>

using namespace std;

Grid GaussSeidel(int x, int y, double dx, double dy, Grid U){

	//define if circle or block
	//enter positive potentials if any
	//enter negative potentials if any
	//enter ground potentials if any

	// sophies way of implementing conditions into geometry - need to use const here for the potentials and grounds, fill all else with non const zeros
	Grid Uold(x,y,dx,dy);
	Grid Unew(x,y,dx,dy);

	//initialse percentage matrix
	double par[x][y]; //this is the percentage of the difference in new iteration and the old iteraton to the iteration new iteration ie (Uold - Unew) / Unew
	for (int i=0; i<x; i++){
		for (int j=0; j<y; j++ ) {
			par[i][j] = 100; //initialise all at 100%
			if (isnan(U[i][j])) {
				Uold[i][j]=0.;
				Unew[i][j]=0.;
			}
			else {
				Uold[i][j] = U[i][j];
				Unew[i][j] = U[i][j];
			}
		}
	}

	int flag=0, n=0, iminus, iplus, jminus, jplus;
	while (flag == 0 && n<1000) {
		flag = 1;
		for (int i=0; i<x; i++){
			for (int j=0; j<y; j++ ) {
				if (! isnan(U[i][j]) ) { //U[i][j] defined as a potential or ground skip it
					Unew[i][j] = U[i][j];
				}
				else if (par[i][j] <= 20) {// 20 percent accuracy
					;
					//do nothing
				}
				else {
					iminus = i-1;
					iplus = i+1;
					jminus = j-1;
					jplus = j+1;

					if (iminus < 0) {
						iminus += x;
					}

					if (iplus > x) {
						iplus -= x;
					}

					if (jminus < 0) {
						jminus += y;
					}

					if (jplus > y) {
						jplus -= y;
					}

					flag = 0; //change the flag if one of the values has changed
					Unew[i][j] = 	( Uold[iplus][j] + Uold[iminus][j] + Uold[i][jminus] + Uold[i][jplus] ) / 4.;
					par[i][j] = ( Unew[i][j] - Uold[i][j] ) / Unew[i][j];
				}
			}

			n++;
		}

	for (int i=0; i<x; i++){
		for (int j=0; j<y; j++) {
			Uold[i][j] = Unew[i][j];
		}
	}
//
	}




return Unew;

//end of file
}