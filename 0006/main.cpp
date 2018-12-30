#include <iostream>

//The sum of the squares of the first ten natural numbers is,
//
// 12 + 22 + ... + 102 = 385
// The square of the sum of the first ten natural numbers is,
//
// (1 + 2 + ... + 10)2 = 552 = 3025
// Hence the difference between the sum of the squares of the first ten natural
// numbers and the square of the sum is 3025 − 385 = 2640.

// Find the difference between the sum of the squares of the first one hundred
// natural numbers and the square of the sum.

constexpr auto long_pow(int base, int exponent) noexcept {
  long pow = 1;
  while(exponent > 0) {
    pow *= base;
    exponent--;
  }
  return pow;
}

constexpr auto sum_till(int upper_bound) noexcept {
  // n(n+1)/2
  return (upper_bound * (upper_bound + 1)) / 2;
}

int main(int argc, char** argv) {
  constexpr auto upper_bound = 100;

  long sum_of_squares = 0;
  for(int i = 1; i <= upper_bound; i++) {
    sum_of_squares += long_pow(i, 2); 
  }

  constexpr long squared_sum = long_pow(sum_till(upper_bound), 2);

  std::cout << "Sum of squares: " << sum_of_squares << std::endl;
  std::cout << "Squared sum: " << squared_sum << std::endl;
  std::cout << "difference: " << squared_sum - sum_of_squares << std::endl;

  return EXIT_SUCCESS;
}
