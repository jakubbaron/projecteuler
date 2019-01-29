#include <iostream>
#include <cmath>
#include <unordered_set>
#include <map>
#include <vector>

// The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.
// 
// There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.
// 
// What 12-digit number do you form by concatenating the three terms in this sequence?

auto is_prime(int n) noexcept -> bool {
  for(int i = 2; i < sqrt(n) + 1; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

auto primes_with_number_of_digits(size_t expected_digits) noexcept -> const std::unordered_set<int> {
    std::unordered_set<int> primes;
    for(int candidate = std::pow(10, expected_digits - 1); candidate < std::pow(10, expected_digits); candidate++) {
      if(is_prime(candidate)) {
        primes.emplace(candidate);
      }
    }

    return primes;
}

auto are_numbers_permutations_of_one_another(const std::vector<int> numbers) noexcept -> bool{
  if(numbers.empty()) {
    return false;
  }

  auto ref = std::to_string(numbers.at(0));
  std::sort(ref.begin(), ref.end());
  for(const auto& number: numbers) {
    auto str_number = std::to_string(number);
    std::sort(begin(str_number), end(str_number));
    if(ref != str_number) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  const auto primes = primes_with_number_of_digits(4);
  for(const auto& prime: primes) {
    for(const auto& prime2: primes) {
      const auto distance = std::abs(prime2 - prime);
      if(distance == 0) {
        continue;
      }
      const auto min_prime = std::min(prime, prime2);
      if(primes.count(min_prime + distance) && primes.count(min_prime + distance + distance)) {
        if(are_numbers_permutations_of_one_another({min_prime, min_prime + distance, min_prime + distance + distance})) { 
          std::cout << min_prime << " " << min_prime + distance << " " << (min_prime + distance + distance) << std::endl;
        }
      }
    }
  }
  return EXIT_SUCCESS;
}
