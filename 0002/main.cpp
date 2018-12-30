#include <iostream>

// Each new term in the Fibonacci sequence is generated by adding the previous two terms. 
// By starting with 1 and 2, the first 10 terms will be:
//
// 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
//
// By considering the terms in the Fibonacci sequence whose values do not exceed four million,
// find the sum of the even-valued terms.

// we can't define a lambda expression in constexpr it'd have to be global, error: variable of non-literal type '(lambda at main.cpp:12:18)' cannot be defined in a constexpr function
// auto is_even = [](const int number) { return (number & 1) == 0; };

constexpr auto is_even(const int number) noexcept {
  return (number & 1) == 0;
}

constexpr auto fibonacci_even_sum(const int UPPER_BOUND) noexcept {
  int last_n_2 = 0;
  int last_n_1 = 1;

  long long sum = 0;
  int current_element = 1;

  while(current_element < UPPER_BOUND) {
    current_element = last_n_2 + last_n_1;
    if(is_even(current_element)) {
      sum += current_element;
    }
    last_n_2 = last_n_1;
    last_n_1 = current_element;
  }

  return sum;
}

int main(int argc, char** argv) {
  constexpr auto UPPER_BOUND = 4000000;
  std::cout << fibonacci_even_sum(UPPER_BOUND) << std::endl; 
  return EXIT_SUCCESS;
}