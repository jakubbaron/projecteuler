#include <iostream>
#include <cmath>
#include <unordered_set>

// It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.
// 
// 9 = 7 + 2×12
// 15 = 7 + 2×22
// 21 = 3 + 2×32
// 25 = 7 + 2×32
// 27 = 19 + 2×22
// 33 = 31 + 2×12
// 
// It turns out that the conjecture was false.
// 
// What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?

auto is_prime(int n) noexcept -> bool {
  for(int i = 2; i < sqrt(n) + 1; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

auto primes_below(int n) noexcept -> const std::unordered_set<int> {
    std::unordered_set<int> primes;
    primes.emplace(2);
    for(int candidate = 2; candidate <= n; candidate++) {
      if(is_prime(candidate)) {
        primes.emplace(candidate);
      }
    }

    return primes;
}

auto is_odd_composite(const int number) noexcept -> bool {
  static const auto primes(primes_below(10000));
  for(int i = 1; i < sqrt(number); i++) {
    if(primes.count(number - 2 * std::pow(i, 2))) {
      return true;
    }
  }
  return false;
}

int main(int argc, char** argv) {
  int number = 33;
  bool notFound = true;
  while(notFound) {
    if(is_prime(number)) {
      number += 2;
      continue;
    }
    if(!is_odd_composite(number)) {
      notFound = false;
      break;
    }

    number+=2;
  }
  std::cout << number << std::endl;
  return EXIT_SUCCESS;
}
