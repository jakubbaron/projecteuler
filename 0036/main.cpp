#include <iostream>
#include <bitset>

// The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.
// 
// Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
// 
// (Please note that the palindromic number, in either base, may not include leading zeros.)

auto is_palindromic(const std::string& str) noexcept -> bool {
  for(int i = 0; i < str.size() / 2; i++) {
    if(str[i] != str[str.size() - 1 - i]) {
      return false;
    }
  }
  return true;
}
auto to_binary(const int number) noexcept -> std::string {
  std::string str = (std::bitset<32>(number)).to_string();
  const auto first_one = str.find('1');
  if(first_one != std::string::npos) {
    str = str.substr(first_one);
  }
  return str;
}

auto sum_of_palindromics(const int upper_bound) noexcept -> int {
  int sum = 0;
  for(int i = 0; i < upper_bound; i++) {
    if(is_palindromic(std::to_string(i)) && is_palindromic(to_binary(i))) {
      sum += i;
    }
  }
  return sum;
}

int main(int argc, char** argv) {
  // std::cout << is_palindromic("585") << std::endl;
  // std::cout << is_palindromic("1001001001") << std::endl;
  // std::cout << is_palindromic("1010") << std::endl;
  // std::cout << is_palindromic("1001") << std::endl;
  // std::cout << to_binary(585) << std::endl;;

  static constexpr auto upper_bound = 1000*1000;
  auto sum = sum_of_palindromics(upper_bound);
  std::cout << "Sum of palindromics: " << sum << std::endl;

  return EXIT_SUCCESS;
}
