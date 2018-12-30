#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
//#include <algorithm>
#include <numeric>

// The four adjacent digits in the 1000-digit number that have the greatest product are 9 × 9 × 8 × 9 = 5832.
//
// 73167176531330624919225119674426574742355349194934
// 96983520312774506326239578318016984801869478851843
// 85861560789112949495459501737958331952853208805511
// 12540698747158523863050715693290963295227443043557
// 66896648950445244523161731856403098711121722383113
// 62229893423380308135336276614282806444486645238749
// 30358907296290491560440772390713810515859307960866
// 70172427121883998797908792274921901699720888093776
// 65727333001053367881220235421809751254540594752243
// 52584907711670556013604839586446706324415722155397
// 53697817977846174064955149290862569321978468622482
// 83972241375657056057490261407972968652414535100474
// 82166370484403199890008895243450658541227588666881
// 16427171479924442928230863465674813919123162824586
// 17866458359124566529476545682848912883142607690042
// 24219022671055626321111109370544217506941658960408
// 07198403850962455444362981230987879927244284909188
// 84580156166097919133875499200524063689912560717606
// 05886116467109405077541002256983155200055935729725
// 71636269561882670428252483600823257530420752963450
//
// Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?

using IntVec = std::vector<int>;
using IntMatrix = std::vector<IntVec>;

const auto display_int_matrix(const IntMatrix& matrix) noexcept {
  for(const auto& line: matrix) {
    for(const auto& item: line) {
      std::cout << std::setw(2) << item;
    }
    std::cout << std::endl;
  }
}

const auto read_int_matrix(std::ifstream& infile) noexcept {
  IntMatrix matrix;
  std::string line;
  while (std::getline(infile, line)) {
    IntVec temp;
    for(int i = 0; i < line.size(); i++) {
      temp.emplace_back(static_cast<int>(line[i] - '0'));
    }
    matrix.emplace_back(std::move(temp));
  }
  return matrix;
}

const auto largest_adjacent_product(const IntMatrix& matrix, const int number_of_adjacent_elements) noexcept {
  long long largest_product = 0;
  for(int row_id = 0; row_id < matrix.size(); row_id++) {
    const auto& row = matrix[row_id];
    for(auto it = row.cbegin(); it != row.cend() - number_of_adjacent_elements; it++) {
      const auto current_product = std::accumulate(it, it + number_of_adjacent_elements, 1, std::multiplies<>());
      if(current_product > largest_product) {
        largest_product = current_product;
      }
    }
  }

  return largest_product;
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

int main(int argc, char** argv) {
  std::ifstream infile("input.txt");
  const auto matrix = read_int_matrix(infile);
  const auto rotated_matrix = rotate_matrix(matrix);

  //display_int_matrix(matrix);
  //std::cout << std::endl;
  //display_int_matrix(rotated_matrix);

  constexpr auto number_of_adjacent_elements = 13;
  const auto result = std::max(largest_adjacent_product(matrix, number_of_adjacent_elements),0LL);//, largest_adjacent_product(rotated_matrix, number_of_adjacent_elements));
  std::cout << "Largest adjacent product is: " << result << std::endl;

  return EXIT_SUCCESS;
}
