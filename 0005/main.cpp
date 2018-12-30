#include <iostream>
#include <set>

// 2520 is the smallest number that can be divided by each of the
// numbers from 1 to 10 without any remainder.
// 
// What is the smallest positive number that is evenly divisible
// by all of the numbers from 1 to 20?

const auto isnt_divisible_by_previous(const int current, std::set<int>& divisors) noexcept {
  for(const auto& item: divisors) {
    if(current % item == 0) {
      return false;
    }
  } 
  std::cout << "Adding " << current << " to set" << std::endl;
  divisors.insert(current);
  return true;
}

const auto smallest_evenly_divisible(const int upper_limit) noexcept { 
  std::set<int> divisors;  
  int product = 1;
  for(int current = 2; current <= upper_limit; current++) {
    if(isnt_divisible_by_previous(current, divisors)) {
      product *= current; 
    }
  }

  const auto base_product = product;
  
  std::set<int> all_numbers; 
  for(int i = 2; i < upper_limit; i++) {
    all_numbers.insert(i);
  }
  bool all_good = false;
  while(!all_good) {
    all_good = true;
    for(const auto& item: all_numbers) {
      if(product % item != 0) {
        product += base_product;
        all_good = false;
        break;
      }
    }
  }

  return product;
}

int main(int argc, char** argv) {
  constexpr auto max_number = 20;
  std::cout << "Smallest product: " << smallest_evenly_divisible(max_number) << std::endl;
  return EXIT_SUCCESS;
}
