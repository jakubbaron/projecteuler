#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

// Starting in the top left corner of a 2×2 grid, and only being able
// to move to the right and down, there are exactly 6 routes to
// the bottom right corner.
// 
// How many such routes are there through a 20×20 grid?

using Vec = std::vector<long>;
using Matrix = std::vector<Vec>;

const auto max_value_in_matrix = [](const Matrix& matrix) {
  long max_matrix_val = 0L;
  for(const auto& row: matrix) {
    const auto max_in_row = *(std::max_element(row.cbegin(), row.cend()));
    max_matrix_val = std::max(max_in_row, max_matrix_val);
  }
  return max_matrix_val;
};

const auto number_of_digits = [](const auto value) {
  return std::to_string(value).size() - 1;
};

const auto print_matrix(const Matrix& matrix) noexcept {
  const auto required_digits = number_of_digits(max_value_in_matrix(matrix)) + 1;

  for(const auto& row: matrix) {
    for(const auto& item: row) {
      std::cout << std::setw(required_digits) << item;
    }
    std::cout << std::endl;
  }
}

const auto init_matrix = [](const auto grid_size) noexcept { 
  Matrix matrix;
  for(int i = 0; i < grid_size; i++) {
    matrix.emplace_back(Vec(grid_size, 0L)); 
  }
  return matrix;
};

const auto find_routes(const size_t grid_size) noexcept {
  const auto corners = grid_size + 1; // we need corners. this on a gird 2x2 we have 3x3 corners

  Matrix matrix = init_matrix(corners);

  //init amount of ways we can get to the left side and to the top side
  for(int i = 0; i < matrix.size(); i++) {
    matrix[i][0] = 1L;
    matrix[0][i] = 1L;
  }

  for(int row = 1; row < matrix.size(); row++) {
    for(int col = 1; col < matrix[row].size(); col++) {
      // the numbers of the ways we can get to the cell is the sum of its top
      // and left neighbours, because we're only going bottom or right
      matrix[row][col] = matrix[row - 1][col] + matrix[row][col-1];
    }
  }

  return matrix[grid_size][grid_size];
}

int main(int argc, char** argv) {
  constexpr auto grid_size = 20;
  std::cout << "There are: " << find_routes(grid_size) << " routes to the bottom right corner" << std::endl;
   
  return EXIT_SUCCESS;
}
