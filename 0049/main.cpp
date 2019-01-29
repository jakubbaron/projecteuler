#include <iostream>
#include <cmath>
#include <set>
#include <map>

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

auto primes_with_number_of_digits(size_t expected_digits) noexcept -> const std::set<int> {
    std::set<int> primes;
    for(int candidate = std::pow(10, expected_digits - 1); candidate < std::pow(10, expected_digits); candidate++) {
      if(is_prime(candidate)) {
        primes.emplace(candidate);
      }
    }

    return primes;
}

int main(int argc, char** argv) {
  const auto primes = primes_with_number_of_digits(4);
  std::map<int, std::map<int, int> > distances;
  for(const auto& prime: primes) {
    for(const auto& prime2: primes) {
      distances[prime][std::abs(prime-prime2)]++;
    }
  }
  for(const auto& item: distances) {
    for(const auto& distance: item.second) {
      const auto& distance_count = distance.second;
      if(distance_count > 2) {
        std::cout << "Prime: " << item.first << " distance: " << distance.first << " count: " << distance_count << std::endl;
      }
    }
  }
  return EXIT_SUCCESS;
}
