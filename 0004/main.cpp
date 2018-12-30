#include <iostream>

// A palindromic number reads the same both ways. The largest palindrome made 
// from the product of two 2-digit numbers is 9009 = 91 × 99.
//
// Find the largest palindrome made from the product of two 3-digit numbers.

constexpr auto int_pow(int base, int exponent) noexcept {
  int pow_result = 1;
  while(exponent > 0) {
    pow_result *= base;
    exponent--;
  }
  return pow_result;
}

auto is_palindrome(int number) noexcept {
  const std::string str_number = std::to_string(number);
  if(str_number.empty()) return false;
  for(int i = 0; i < str_number.size() / 2; i++) {
    if(str_number[i] != str_number[str_number.size() - 1 - i]) {
      return false;
    }
  }

  return true;
}

constexpr auto largest_palindrome(const int number_of_digits) noexcept {
  const auto lower_bound = int_pow(10, number_of_digits - 1);
  auto largest_palindrome = 0;
  for(int i = int_pow(10, number_of_digits) - 1; i >= lower_bound; i--) {
    for(int j = i; j >= lower_bound; j--) {
      const auto result = i * j;
      if(is_palindrome(result)) {
        if(result > largest_palindrome) {
          largest_palindrome = result;
        }
      }
    }
  }
  return largest_palindrome;
}

int main(int argc, char** argv) {
  constexpr auto number_of_digits = 3;
  std::cout << "Largest palindrome: " << largest_palindrome(number_of_digits) << std::endl;

  return EXIT_SUCCESS;
}
