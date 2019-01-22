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

auto display_matrix = [](const Matrix& matrix) -> void {
  for(int col = 0; col < matrix.size(); col++) { 
    for(int row = 0; row < matrix[col].size(); row++) {
      std::cout << matrix[col][row] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "NEXT" << std::endl;
};

auto form_a_spiral = [](const int size) -> Matrix {
  Matrix matrix;
  for(int i = 0; i < size; i++) {
    matrix.emplace_back(IntVec(size, 0));
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
    // Right -> start?
    // Down
    std::cout << "DOWN" << std::endl;
    for(int i = 0; i < number_of_elements; i++) {
      matrix[row][col] = current_element++;
      row++;
      display_matrix(matrix);
    }
    // Left
    std::cout << "LEFT" << std::endl;
    row--;
    col--;
    for(int i = 0; i < number_of_elements; i++) {
      matrix[row][col] = current_element++;
      col--;
      display_matrix(matrix);
    }
    col++;
    row--;
    // Up
    std::cout << "UP" << std::endl;
    for(int i = 0; i < number_of_elements; i++) {
      matrix[row][col] = current_element++;
      row--;
      display_matrix(matrix);
    }
    // Right
    row++;
    col++;
    std::cout << "RIGHT" << std::endl;
    for(int i = 0; i< number_of_elements; i++) {
      matrix[row][col] = current_element++;
      col++;
      display_matrix(matrix);
    }
    row++;
    number_of_elements++;
  }

  return matrix;
};

int main(int argc, char** argv) {
  Matrix matrix = form_a_spiral(5);
  display_matrix(matrix);

  return EXIT_SUCCESS;
}
