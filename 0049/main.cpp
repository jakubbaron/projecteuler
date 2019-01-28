#include <iostream>

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

auto primes_below(int n) noexcept -> const std::set<int> {
    std::set<int> primes;
    primes.emplace(2);
    for(int candidate = 2; candidate <= n; candidate++) {
      if(is_prime(candidate)) {
        primes.emplace(candidate);
      }
    }

    return primes;
}

int main(int argc, char** argv) {

  return EXIT_SUCCESS;
}
