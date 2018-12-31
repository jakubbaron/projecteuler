#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>

// In the 20×20 grid below, four numbers along a diagonal line have been marked in red.
// 
// 08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
// 49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
// 81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
// 52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
// 22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
// 24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
// 32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
// 67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
// 24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
// 21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
// 78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
// 16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
// 86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
// 19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
// 04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
// 88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
// 04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
// 20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
// 20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
// 01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
// 
// The product of these numbers is 26 × 63 × 78 × 14 = 1788696.
// 
// What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20×20 grid?


using IntVec = std::vector<int>;
using IntMatrix = std::vector<IntVec>;

const auto display_int_matrix(const IntMatrix& matrix) noexcept {
  for(const auto& line: matrix) {
    for(const auto& item: line) {
      std::cout << std::setw(3) << item;
    }
    std::cout << std::endl;
  }
}

const auto read_int_matrix(std::ifstream& infile) noexcept {
  IntMatrix matrix;
  std::string line;
  while (std::getline(infile, line)) {
    IntVec temp_vec;
    std::stringstream ss;     
    ss << line;
    while (!ss.eof()) { 
      int temp{0};
      ss >> temp;
      temp_vec.emplace_back(temp);
    }
    matrix.emplace_back(std::move(temp_vec));
  }
  return matrix;
}

const auto rotate_matrix(const IntMatrix& in_matrix) noexcept {
  IntMatrix matrix;
  for(int col = 0; col < in_matrix[0].size(); col++) {
    IntVec temp;
    for(int row= 0; row< in_matrix.size(); row++) {
      temp.emplace_back(in_matrix[row][col]);
    }
    matrix.emplace_back(std::move(temp));
  }
  return matrix;
}

const auto largest_adjacent_product_left_right(const IntMatrix& matrix, const int number_of_adjacent_elements) noexcept {
  long long largest_product = 0LL;
  for(int row_id = 0; row_id < matrix.size(); row_id++) {
    const auto& row = matrix[row_id];
    for(auto it = row.cbegin(); it != row.cend() - number_of_adjacent_elements; it++) {
      const auto current_product = std::accumulate(it, it + number_of_adjacent_elements, 1LL, std::multiplies<>());
      largest_product = std::max(current_product, largest_product);
    }
  }

  return largest_product;
}
const auto largest_adjacent_product_diagonal_left_right_down(const IntMatrix& matrix, const int number_of_adjacent_elements) noexcept { 
  long long largest_product = 0LL;
  for(int row = 0; row < matrix.size() - number_of_adjacent_elements; row++) {
    for(int col = 0; col < matrix[row].size() - number_of_adjacent_elements; col++) {
      IntVec temp_vec;
      for(int id = 0; id < number_of_adjacent_elements; id++) {
        temp_vec.emplace_back(matrix[row+id][col+id]);
      }
      const auto current_product = std::accumulate(cbegin(temp_vec), cend(temp_vec), 1LL, std::multiplies<>());
      largest_product = std::max(current_product, largest_product);
    }
  }

  return largest_product;
}

const auto largest_adjacent_product_diagonal_left_right_up(const IntMatrix& matrix, const int number_of_adjacent_elements) noexcept { 
  return largest_adjacent_product_diagonal_left_right_down(rotate_matrix(matrix), number_of_adjacent_elements);
}

const auto largest_adjacent_product_top_down(const IntMatrix& matrix, const int number_of_adjacent_elements) noexcept {
  long long largest_product = 0LL;
  for(int row = matrix.size() - 1; row > number_of_adjacent_elements; row--) {
    for(int col = 0; col < matrix[rowt].size() - number_of_adjacent_elements; col++) {
      IntVec temp_vec;
      for(int id = 0; id < number_of_adjacent_elements; id++) {
        temp_vec.emplace_back(matrix[row-id][col+id]);
      }
      const auto current_product = std::accumulate(cbegin(temp_vec), cend(temp_vec), 1LL, std::multiplies<>());
      largest_product = std::max(current_product, largest_product);
    }
  }

  return largest_product;
}

int main(int argc, char** argv) {
  std::ifstream infile("input.txt");
  const auto matrix = read_int_matrix(infile);
  constexpr auto number_of_adjacent_elements = 4;
  // left right and right left product will be the same
  // the same applies to top down, down top
  std::cout << "left right " << largest_adjacent_product_left_right(matrix, number_of_adjacent_elements) << std::endl;
  std::cout << "top down " << largest_adjacent_product_top_down(matrix, number_of_adjacent_elements)<< std::endl;
  std::cout << "diagonal down " << largest_adjacent_product_diagonal_left_right_down(matrix, number_of_adjacent_elements)<< std::endl;
  std::cout << "diagonal up "<< largest_adjacent_product_diagonal_left_right_up(matrix, number_of_adjacent_elements)<< std::endl;

  const auto result = std::max({largest_adjacent_product_left_right(matrix, number_of_adjacent_elements), 
                                largest_adjacent_product_top_down(matrix, number_of_adjacent_elements),
                                largest_adjacent_product_diagonal_left_right_down(matrix, number_of_adjacent_elements),
                                largest_adjacent_product_diagonal_left_right_up(matrix, number_of_adjacent_elements)
                              });

  std::cout << "Largest product of " << number_of_adjacent_elements << " adjacent elements is: " << result << std::endl;

  return EXIT_SUCCESS;
}
