#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

// Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
// 
// 1634 = 14 + 64 + 34 + 44
// 8208 = 84 + 24 + 04 + 84
// 9474 = 94 + 44 + 74 + 44
// As 1 = 14 is not a sum it is not included.
// 
// The sum of these numbers is 1634 + 8208 + 9474 = 19316.
// 
// Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.

auto get_sum_of_digits_to_power = [](const int number, const int powers) -> int {
  int sum = 0;
  for(const char& c: std::to_string(number)) {
    sum += std::pow(static_cast<int>(c - '0'), powers); 
  }
  return sum;
}; 

auto min_number = [](int powers) -> int {
  int i = 12;
  return get_sum_of_digits_to_power(i, powers);
};

auto max_number = [](int powers) -> int {
  size_t max_digits = 0;
  size_t last_seen_digits = 0;
  return std::pow(9, powers) * powers;
};

auto sum_of_powers_of_digits = [](int powers) -> int {
  std::vector<int> valid_numbers;

  for(int i = min_number(powers); i < max_number(powers); i++) {
    if(get_sum_of_digits_to_power(i, powers) == i) {
      valid_numbers.emplace_back(i);
    }
  }

  return std::accumulate(begin(valid_numbers), end(valid_numbers), 0);
};

int main(int argc, char** argv) {
  std::cout << "Max number for fifth powers: " << max_number(5) << std::endl;
  std::cout << "Min number for fifth powers: " << min_number(5) << std::endl;
  std::cout << "Sum of numbers to fourth powers: " << sum_of_powers_of_digits(4) << std::endl;
  std::cout << "Sum of numbers to fith powers: " << sum_of_powers_of_digits(5) << std::endl;

  return EXIT_SUCCESS;
}
