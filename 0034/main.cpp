#include <iostream>
#include <vector>

// 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
//
// Find the sum of all numbers which are equal to the sum of the factorial of their digits.
// 
// Note: as 1! = 1 and 2! = 2 are not sums they are not included.

auto factorial(int n) noexcept -> int {
  if(n > 10) return -1;
  static std::vector<int> factorials(10, 0);

  if(n == 0 || n == 1) {
    return 1;
  }

  if(factorials[n] != 0) {
    return factorials[n];
  } else {
    factorials[n] = n * factorial(n-1);
    return factorials[n];
  }
}

auto sum_of_numbers_equal_to_sum_of_factorials() noexcept -> int {
  int sum = 0;
  for(int i = 3; i < factorial(9); i++) {
    int factorial_sum = 0;
    for(const auto& c: std::to_string(i)) {
      factorial_sum += factorial(static_cast<int>(c - '0'));
    }
    if(factorial_sum == i) {
      sum += i;
    }
  }
  return sum;
}

int main(int argc, char** argv) {
  auto sum = sum_of_numbers_equal_to_sum_of_factorials();
  std::cout << "Sum is: " << sum << std::endl;
  return EXIT_SUCCESS;
}
