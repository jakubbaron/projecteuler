#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

// A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
// 
// 012   021   102   120   201   210
// 
// What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?

int main(int argc, char** argv) {
  std::vector<std::string> permutations;
  std::string digits = "0123456789";
  permutations.emplace_back(digits);
  while(std::next_permutation(digits.begin(), digits.end())) {
    permutations.emplace_back(digits);  
  }
  std::sort(permutations.begin(), permutations.end());
  std::cout << "Millionth: " << permutations[1000000-1] << std::endl;
  return EXIT_SUCCESS;
}
