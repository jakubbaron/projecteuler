#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>

// A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:
// 
// 1/2	= 	0.5
// 1/3	= 	0.(3)
// 1/4	= 	0.25
// 1/5	= 	0.2
// 1/6	= 	0.1(6)
// 1/7	= 	0.(142857)
// 1/8	= 	0.125
// 1/9	= 	0.(1)
// 1/10	= 	0.1
// Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
// 
// Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.

auto get_as_fraction = [](int n, const int max_digits = 10000) {
  if(n == 0) { 
    return std::make_pair(std::string("0"), size_t(0));
  }

  std::string output;
  int carry_over = 10;;
  int current_digits = 0;
  while(carry_over != 0 && current_digits < max_digits) {
    int next_place = carry_over / n;
    carry_over -= (next_place * n);
    std::string str_carry_over = std::to_string(carry_over);
    carry_over *= 10;
    // std::cout << "CarryOver: " << carry_over << " NextPlace: " << next_place << std::endl;
    output += std::to_string(next_place);
    current_digits++;
  }
  bool repeated = false;
  size_t start_len = std::to_string(n).size();
  size_t len = start_len;
  for(int start = 0; start < output.length() / 2 && !repeated; start++) {
    for(len = start_len; len < output.length() / 2; len++) {
      std::string checking = output.substr(start, len);
      std::string second = output.substr(start + len, len );
      //std::cout << "Checking: " << checking << " second: " << second << std::endl;
      if(checking == second) {
        repeated = true;
        break;
      }
    }
  }
  return std::make_pair(output, repeated ? len : size_t(0));
};

int main(int argc, char** argv) {
  static auto constexpr upper_bound = 1000;
  std::vector<int> max_digits;
  for(int i = 0; i < upper_bound; i++) {
    const auto fr = get_as_fraction(i);
    max_digits.emplace_back(fr.second);
  }
  std::cout << "Number with max recurring cycle: " << std::distance(max_digits.begin(), std::max_element(max_digits.begin(), max_digits.end())) << std::endl;
  return EXIT_SUCCESS;
}
