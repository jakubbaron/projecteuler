#include <iostream>
#include <vector>

// The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.
// 
// Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:
// 
// d2d3d4=406 is divisible by 2
// d3d4d5=063 is divisible by 3
// d4d5d6=635 is divisible by 5
// d5d6d7=357 is divisible by 7
// d6d7d8=572 is divisible by 11
// d7d8d9=728 is divisible by 13
// d8d9d10=289 is divisible by 17
// Find the sum of all 0 to 9 pandigital numbers with this property.

auto string_to_int(const std::string& str) noexcept -> uint64_t {
  // normally we'd check if there are only 0-9 characters, but we assume that
  // we don't pass anything 'evil'
  uint64_t out = 0;
  static const std::vector<uint64_t> pows = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
  for(uint64_t i = 0; i < str.length(); i++) {
    out += static_cast<uint64_t>(str[i] - '0') * pows[str.length() - i - 1];
  }

  return out;
}

auto is_interesting(const std::string& number) noexcept -> bool {
  static const std::vector<int> dividers = {2, 3, 5, 7, 11, 13, 17};
  auto numbers = [](const std::string& number) {
    std::vector<uint64_t> temp;
    for(int i = 1; i <= 7; i++) {
      temp.emplace_back(string_to_int(number.substr(i, 3)));
    }
    return temp;
  };

  auto check_divisibility = [](const auto nums) {
    for(int i = 0; i < nums.size(); i++) {
      if(nums[i] % dividers[i] != 0) {
        return false;
      }
    }
    return true;
  };

  return check_divisibility(numbers(number));
}

auto sum_of_interesting_pandigitals() noexcept -> uint64_t {
  uint64_t sum = 0;
  std::string digits = "0123456789";
  do{
    if(is_interesting(digits)) {
      std::cout << "Is interesting: " << digits << std::endl;
      sum += string_to_int(digits);
    }
  } while(std::next_permutation(digits.begin(), digits.end()));

  return sum;
}

int main(int argc, char** argv) {
  std::cout << "Interesting numbers' sum: " << sum_of_interesting_pandigitals() << std::endl; 
  return EXIT_SUCCESS;
}
