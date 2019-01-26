#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

// Take the number 192 and multiply it by each of 1, 2, and 3:
// 
// 192 × 1 = 192
// 192 × 2 = 384
// 192 × 3 = 576
// By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)
// 
// The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).
// 
// What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?

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

int main(int argc, char** argv) {
  std::string max_padigital = "123456789";
  for(int i = 1; i < 123456789; i++) {
    std::string str;
    int n = 1;
    while(str.size() < 9) {
      str += std::to_string(i * n++);
    }
    if(str.size() != 9) {
      continue;
    }
    if(is_pandigital(str)) {
      max_padigital = std::max(str, max_padigital); 
    }
  }
  std::cout << max_padigital << std::endl;
  return EXIT_SUCCESS;
}
