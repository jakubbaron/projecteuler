#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <iomanip>

using Vec = std::vector<int>;
using Triangle = std::vector<Vec>;

const auto read_int_triangle(std::ifstream& infile) {
  Triangle triangle;
  std::string line;
  size_t last_level_size = 0;
  while (std::getline(infile, line)) {
    Vec temp_vec;
    std::stringstream ss;     
    ss << line;
    while (!ss.eof()) { 
      int temp{0};
      ss >> temp;
      temp_vec.emplace_back(temp);
    }
    if(last_level_size != temp_vec.size() - 1) {
      throw std::invalid_argument("Input file is invalid, triangle isn't valid");
    }
    last_level_size = temp_vec.size();
    triangle.emplace_back(std::move(temp_vec));
  }
  return triangle;
}

const auto display_int_triangle(const Triangle& triangle) noexcept {
  for(const auto& line: triangle) {
    for(const auto& item: line) {
      std::cout << std::setw(3) << item;
    }
    std::cout << std::endl;
  }
}

const auto find_best_routes(const Triangle& triangle) noexcept {
  Triangle best_routes = triangle; //copy the triangle as we'll want to add the cell values to the best routes anyway

  for(int row = 1; row < triangle.size(); row++) {
    for(int position = 0; position < triangle[row].size(); position++) {
      const auto previous_row = row - 1;
      auto top_left = 0;
      auto top_right = 0;
      if(position != 0) {
        top_left = best_routes[previous_row][position - 1];
      }
      if(position != best_routes[previous_row].size()) {
        top_right = best_routes[previous_row][position];
      }
      best_routes[row][position] += std::max(top_left, top_right);
    }
  }
  return best_routes;
}

// By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
// 
// 3
// 7 4
// 2 4 6
// 8 5 9 3
// 
// That is, 3 + 7 + 4 + 9 = 23.
// Find the maximum total from top to bottom of the triangle below:
// 
// 75
// 95 64
// 17 47 82
// 18 35 87 10
// 20 04 82 47 65
// 19 01 23 75 03 34
// 88 02 77 73 07 63 67
// 99 65 04 28 06 16 70 92
// 41 41 26 56 83 40 80 70 33
// 41 48 72 33 47 32 37 16 94 29
// 53 71 44 65 25 43 91 52 97 51 14
// 70 11 33 28 77 73 17 78 39 68 17 57
// 91 71 52 38 17 14 91 43 58 50 27 29 48
// 63 66 04 68 89 53 67 30 73 16 69 87 40 31
// 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
//
// NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)

int main(int argc, char** argv) {
  std::ifstream infile("input.txt");
  const auto triangle = read_int_triangle(infile);
  const auto best_routes = find_best_routes(triangle);
  const auto best_route = *std::max_element(best_routes[best_routes.size() - 1].cbegin(), best_routes[best_routes.size() - 1].cend());
  std::cout << "Best route's value is: " << best_route << std::endl;
  return EXIT_SUCCESS;
}
