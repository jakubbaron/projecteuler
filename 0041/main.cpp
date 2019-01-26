#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <cmath>

// We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
// 
// What is the largest n-digit pandigital prime that exists?
auto string_to_int(const std::string& str) noexcept -> int {
  // normally we'd check if there are only 0-9 characters, but we assume that
  // we don't pass anything 'evil'
  int out = 0;
  static const std::vector<int> pows = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
  for(int i = 0; i < str.length(); i++) {
    out += static_cast<int>(str[i] - '0') * pows[str.length() - i - 1];
  }

  return out;
}

auto is_pandigital(const std::string& numbers) noexcept -> bool {
  if(numbers.size() != 9) return false;

  std::set<char> digits; 
  for(const auto& c: numbers) {
    if(digits.count(c)) {
      return false;
    }  
    digits.insert(c);
  }
  return !digits.count('0') && (digits.size() == 9);
}
auto is_prime(int n) noexcept -> bool {
  for(int i = 2; i < sqrt(n) + 1; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

auto biggest_n_digit_pandigital_prime() noexcept -> int {
  std::string max_padigital = "123456789";
  int max_prime = 0;
  for(int i = 1; i <= max_padigital.size(); i++) {
    std::string digits = max_padigital.substr(0, i);
    do{
      if(is_prime(string_to_int(digits))) {
        max_prime = std::max(string_to_int(digits), max_prime);
      }
    } while(std::next_permutation(digits.begin(), digits.end()));
  }
  return max_prime;
}

int main(int argc, char** argv) {
  const auto result = biggest_n_digit_pandigital_prime();
  std::cout << "Max prime: " << result << std::endl;
  return EXIT_SUCCESS;
}
