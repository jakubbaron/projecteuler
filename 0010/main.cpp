#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
//
// Find the sum of all the primes below two million.

const auto is_prime(int n) noexcept {
  for(int i = 2; i < static_cast<int>(sqrt(n)) + 1; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

const auto primes_below(const int upper_bound) noexcept {
  std::vector<int> primes;
  for(int i = 2; i <= upper_bound; i++) {
    if(is_prime(i)) {
      primes.emplace_back(i);
    }
  }
  return primes;
}

const auto sum_of_primes_below(const int upper_bound) noexcept {
  const auto primes = primes_below(upper_bound);
  long long sum =  std::accumulate(primes.cbegin(), primes.cend(), 0LL);
  return sum;
}

int main(int argc, char** argv) {
  constexpr auto upper_bound = 2 * 1000 * 1000;
  std::cout << "Sum of primes below " << upper_bound << " is: " << sum_of_primes_below(upper_bound) << std::endl;
  return EXIT_SUCCESS;
}
