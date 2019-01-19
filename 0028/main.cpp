#include <iostream>
#include <vector>

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

auto form_a_spiral = [](const int size) -> Matrix {
  Matrix matrix;
  for(int i = 0; i < size; i++) {
    matrix.emplace_back(IntVec(size, 0));
  }
  int mid = size / 2;
  int elements = size * size;
  int current_element = 1;
  int col = mid;
  int row = mid;
  int last_length = 1;

  while(current_element <= elements) {
    matrix[col][row] = current_element++;
  }

  return matrix;
};

auto display_matrix = [](const Matrix& matrix) -> void {
  for(int col = 0; col < matrix.size(); col++) { 
    for(int row = 0; row < matrix[col].size(); row++) {
      std::cout << matrix[col][row] << " ";
    }
    std::cout << std::endl;
  }  
};

int main(int argc, char** argv) {
  Matrix matrix = form_a_spiral(5);
  display_matrix(matrix);

  return EXIT_SUCCESS;
}
