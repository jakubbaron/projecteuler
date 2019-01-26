#include <iostream>
#include <map>

// If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
// 
// {20,48,52}, {24,45,51}, {30,40,50}
// 
// For which value of p ≤ 1000, is the number of solutions maximised?

constexpr auto is_valid_right_triangle(int a, int b, int c) noexcept -> bool {
  return ((a * a) + (b * b)) == (c * c);
}

constexpr auto how_many_solutions(const int p) noexcept -> size_t {
  size_t count = 0;
  for(int a = 1; a < p; a++) {
    for(int b = a + 1; b < p; b++) {
      for(int c = b + 1; c < p; c++) {
        if((a + b + c) == p && is_valid_right_triangle(a, b, c)) {
          count++;
        }
      }
    }
  }
  return count;
}

auto solutions_maximised(const int p) noexcept -> int { 
  std::map<int, size_t> number_of_solutions;
  for(int i = 1; i <= p; i++) {
    number_of_solutions.emplace(std::make_pair(i, how_many_solutions(i)));
  }
  size_t max_item = 0;
  int max_p = 0;
  for(const auto& item: number_of_solutions) {
    //std::cout << item.first << " " << item.second << std::endl;
    if(max_item < item.second) {
      max_item = std::max(max_item, item.second);
      max_p = item.first;
    }
  }

  return max_p;
}

int main(int argc, char** argv) {
  static constexpr auto upper_bound = 1000;
  const auto result = solutions_maximised(upper_bound);
  std::cout << "Result: " << result << std::endl;
  return EXIT_SUCCESS;
}
