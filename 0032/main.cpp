#include <iostream>
#include <numeric>
#include <set>
#include <vector>
#include <cmath>

// We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
// 
// The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.
// 
// Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
// 
// HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

auto string_to_int(const std::string& str) noexcept -> uint32_t {
  // normally we'd check if there are only 0-9 characters, but we assume that
  // we don't pass anything 'evil'
  uint32_t out = 0;
  static const std::vector<uint32_t> pows = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
  for(int i = 0; i < str.length(); i++) {
    out += static_cast<uint32_t>(str[i] - '0') * pows[str.length() - i - 1];
  }

  return out;
}

auto check_identity_for_pandigital(std::vector<uint32_t> numbers) noexcept -> bool {
  std::set<char> digits; 
  for(const auto& number: numbers) {
    for(const auto& c: std::to_string(number)) {
      if(digits.count(c)) {
        return false;
      }  
      digits.insert(c);
    }
  }
  return !digits.count('0') && (digits.size() == 9);
}

auto sum_of_pandigitals() noexcept -> uint32_t {
  std::set<uint32_t> pandigitals;
  std::string digits = "123456789";
  // if we take longer than 4-digit number and multiply it by another number, we can get either 4-digit number or 5-digit number
  // that means that we'll no longer be able to fit that our 1-9 pandigital
  constexpr auto max_digits = 7;

  do {
    for(int i = 1; i <= max_digits; i++) {
      auto first_number = string_to_int(digits.substr(0, i));
      for(int j = 1; j <= max_digits - i; j++) {
        auto second_number = string_to_int(digits.substr(i, j));
        auto product = first_number * second_number;
        //std::cout << "Digits[" << digits << "] first number[" << first_number << "]\tsecond number[" << second_number << "]\tproduct[" << product << "]" << std::endl;
        if(check_identity_for_pandigital({first_number, second_number, product})) {
          //This till print several times because the permutations might have the very same beginning 
          std::cout << "Found pandigital! First number[" << first_number << "]\tsecond number[" << second_number << "]\tproduct[" << product << "]" << std::endl;
          pandigitals.insert(product);
        }
      }
    }
  } while(std::next_permutation(digits.begin(), digits.end()));

  return std::accumulate(begin(pandigitals), end(pandigitals), 0);
}

int main(int argc, char** argv) {
  // std::cout << string_to_int("123455") << std::endl;
  // std::cout << check_identity_for_pandigital({123, 456, 7819}) << std::endl;
  // std::cout << check_identity_for_pandigital({123, 456, 789}) << std::endl;
  auto result = sum_of_pandigitals();
  std::cout << "Result is: " << result << std::endl;
  return EXIT_SUCCESS;
}
