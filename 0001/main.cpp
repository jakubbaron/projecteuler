#include <iostream>

// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. 
// The sum of these multiples is 23.
// Find the sum of all the multiples of 3 or 5 below 1000.

constexpr auto sum_of_multiples(const int base_multiple, int UPPER_BOUND) noexcept {
  int sum = 0;
  int multiple = base_multiple;
  while(multiple < UPPER_BOUND) {
    sum += multiple;
    multiple += base_multiple;
  }
  return sum;
}

constexpr auto sum_of_multiples_skip(const int base_multiple, const int skip_multiple, int UPPER_BOUND) noexcept {
  int sum = 0;
  int helper_index = 1;
  int multiple = base_multiple;

  while(multiple < UPPER_BOUND) {
    // We're counting this way as modulos are expensive :)
    if(helper_index == skip_multiple) {
      helper_index = 1;
      multiple += base_multiple;
      continue;
    }

    sum += multiple;
    multiple += base_multiple;
    helper_index++;
  }

  return sum;
}

int main(int argc, char** argv) {
  constexpr auto UPPER_BOUND = 1000;
  constexpr auto multiple_1 = 3;
  constexpr auto multiple_2 = 5;
  constexpr auto sum_of_two_multiples = sum_of_multiples(multiple_1, UPPER_BOUND) + sum_of_multiples_skip(multiple_2, multiple_1, UPPER_BOUND);
  std::cout << sum_of_two_multiples << std::endl;
  return EXIT_SUCCESS;
}
