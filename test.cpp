#include <iostream>
#include "Grid.h"
#include <iomanip>

int main(){

//std::cout << "This is a test to see if i can include the grid source file properly" << std::endl;

int N=4,M=4,x=N*M,y=N*M; // n and m are cell sizes of the single blocks (boundary control)
float dx=0.1,dy=0.2; // dx dy need to be floats for mathy reasons

Grid mygrid(x,y,dx,dy); //make the const grid thing with grid ?? who knows really

for ( int i = 0; i<x; i++ ){
mygrid[i][i] = -2*(1/(dx*dx) + 1/(dy*dy)); // sets main diagonal as the big differential thing
}

for ( int i = 0; i<N-1; i++ ) {
    for ( int j = 0; j<M; j++ ) {
           mygrid[i+(j*N)][i+(j*N)+1] = 1/(dx*dx); //sets secondary diags as dx thing
           mygrid[(i+(j*N)+1)][i+(j*N)] = 1/(dx*dx);
    }
}

for ( int i = 0; i<N; i++ ) {
    for ( int j = 0; j<M-1; j++ ) {
           mygrid[i+(j*N)][i+((j+1)*N)+1] = 1/(dy*dy); //sets n+1th diagonal as the dy thing
           mygrid[(i+((j+1)*N)+1)][i+(j*N)] = 1/(dy*dy);
    }
}

mygrid[(N*M - N)][0] = 0; // the dy loop goes to far and always hits the "nth" column, but in c we go from 0 to n-1, so this can just be automatically set to 0. this is because i am not only a bad programmer. but also a lazy one :)

for ( int i = 0; i<x; i++ ) {
	for ( int j = 0; j<y; j++ ) { //remember for all loops here that our grid was defined the wrong way round, i.e y by x, instead of x by y. So all the [i][j] shit is flipped at the end to [j][i].. or something?
		std::cout << std::right << std::setw(5) << mygrid[j][i]; //using iomanip header to acces std::right and std::setw, allows control of buffer size for character strings or something. so the matrix doesnt skew with large amounts of numbers and go horrible
	}
std::cout << std::endl; // takes a new line after every jth row of ith columns
}


return 0;

}
