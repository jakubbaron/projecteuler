#include <iostream>
#include <vector>
#include <iomanip>

// Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
// 
// 21 22 23 24 25
// 20  7  8  9 10
// 19  6  1  2 11
// 18  5  4  3 12
// 17 16 15 14 13
// 
// It can be verified that the sum of the numbers on the diagonals is 101.
// 
// What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?

using IntVec = std::vector<int>;
using Matrix = std::vector<IntVec>;

auto display_matrix = [](const Matrix& matrix) -> void {
  for(int col = 0; col < matrix.size(); col++) { 
    for(int row = 0; row < matrix[col].size(); row++) {
      std::cout << std::setw(3) << matrix[col][row] << " ";
    } std::cout << std::endl;
  }
  std::cout << std::endl;
};

auto form_a_spiral = [](const int size) -> Matrix {
  Matrix matrix;
  for(int i = 0; i < size; i++) {
    matrix.emplace_back(IntVec(size, 0));
  }
  if(size % 2 != 1) {
    std::cout << "Not supported size, only odd sizes are acceptable" << std::endl;
    return matrix;
  }

  int mid = size / 2;
  int elements = size * size;
  int current_element = 1;
  matrix[mid][mid] = current_element++;
  int col = mid;
  int row = mid;
  
  //how many elements to insert per rotation
  int number_of_elements = 2;
  col++;
  while(current_element <= elements) {
    // Down
    for(int i = 0; i < number_of_elements; i++) {
      matrix[row][col] = current_element++;
      row++;
    }
    // Left
    row--;
    col--;
    for(int i = 0; i < number_of_elements; i++) {
      matrix[row][col] = current_element++;
      col--;
    }
    col++;
    row--;
    // Up
    for(int i = 0; i < number_of_elements; i++) {
      matrix[row][col] = current_element++;
      row--;
    }
    // Right
    row++;
    col++;
    for(int i = 0; i< number_of_elements; i++) {
      matrix[row][col] = current_element++;
      col++;
    }
    number_of_elements += 2 ;
  }

  return matrix;
};

auto sum_diagonals = [](const Matrix& matrix) -> uint32_t {
  //TODO check if it's a square?
  uint32_t sum = 0;
  for(int i = 0; i < matrix.size(); i++) {
    sum += matrix[i][i] + matrix[matrix.size() - i - 1][i];
  }
  
  return sum - 1 /* mid point counter twice */;
};

int main(int argc, char** argv) {
  Matrix matrix = form_a_spiral(1001);
  //display_matrix(matrix);
  std::cout << "Sum of diagonals: " << sum_diagonals(matrix) << std::endl;

  return EXIT_SUCCESS;
}
