/* Program to multiply two matrices */

#include <iostream>

int main() {
  //do input in functions next time?
  //take input of matrix 1
  std::cout << "Please enter the dimension of your first matrix: ";
  int iOne, jOne;
  std::cin >> iOne;
  std::cin >> jOne;
  if ( iOne > 100 || jOne > 100 ) {
    std::cout << "Too big matrix.";
    return 1;
  }

  std::cout << "Please enter your first matrix: ";

  //i is rows, j is column
  int matrixOne[100][100];
  for ( int i=0; i < iOne; i++ ) {
    for ( int j=0; j < jOne; j++ ) {
      std::cin >> matrixOne[i][j];
    }
  }

  //take input of second matrix
  std::cout << "Please enter the dimension of your second matrix: ";
  int iTwo, jTwo;
  std::cin >> iTwo;
  std::cin >> jTwo;
  if ( iTwo > 100 || jTwo > 100 ) {
    std::cout << "Too big matrix.";
    return 1;
  }

  std::cout << "Please enter your second matrix: ";

  //i is rows, j is column
  int matrixTwo[100][100];
  for ( int i=0; i < iTwo; i++ ) {
    for ( int j=0; j < jTwo; j++ ) {
      std::cin >> matrixTwo[i][j];
    }
  }

  //check the multiplication can work
  if ( jOne != iTwo ) {
    std::cout << "Matrix dimensions wrong. Please enter two matrices that can be multiplied. ";
    std::cout<< "The number of columns in the first should match the rows in the second.";
    std::cout << std::endl;
    return 2;
  }

  //multiply
  int result[100][100];
  for ( int i=0; i<iOne; i++ ) {
    std::cout << i << std::endl;
    for ( int j=0; j<jTwo; j++ ) {
      std::cout << j << std::endl;
      for ( int k=0; k<jOne; k++ ) {
	result[i][j] += matrixOne[i][k] * matrixTwo[k][j];
      }
    }
  }

  //display result
  std::cout << "Your matrix is:" << std::endl;
  for ( int i=0; i < iOne; i++ ) {
    for ( int j=0; j < jTwo; j++ ) {
      std::cout << result[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
