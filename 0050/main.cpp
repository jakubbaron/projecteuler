#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

// The prime 41, can be written as the sum of six consecutive primes:
//
// 41 = 2 + 3 + 5 + 7 + 11 + 13
// This is the longest sum of consecutive primes that adds to a prime below one-hundred.
// 
// The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
// 
// Which prime, below one-million, can be written as the sum of the most consecutive primes?

auto is_prime(int n) noexcept -> bool {
  for(int i = 2; i < sqrt(n) + 1; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

auto primes_below(int n) noexcept -> const std::vector<int> {
    std::vector<int> primes;
        primes.emplace_back(2);
    for(int candidate = 2; candidate <= n; candidate++) {
      if(is_prime(candidate)) {
        primes.emplace_back(candidate);
      }
    }

    return primes;
}

auto longest_consecutive_prime_below(int n) noexcept -> std::pair<int, int> {
  const auto primes = primes_below(n);
  std::vector<int> prime_sum(primes.size() + 1, 0);
  for(int i = 0; i < primes.size(); i++) {
    prime_sum[i+1] = prime_sum[i] + primes[i];
  }
  int number_of_primes = 0;
  int result = 0;
  for(int i = number_of_primes; i < prime_sum.size(); i++) {
    for(int j = i - (number_of_primes + 1); j >= 0; j--) {
      const auto sum = prime_sum[i] - prime_sum[j];
      if(sum > n) {
        break;
      }

      if(std::binary_search(begin(primes), end(primes), sum)) {
        number_of_primes = i - j;
        result = sum;
      }
    }
  }

  return std::make_pair(number_of_primes, result);
}

int main(int argc, char** argv) {
  const auto result = longest_consecutive_prime_below(1000*1000);
  std::cout << "Count: " << result.first << " Prime: " << result.second << std::endl;
  return EXIT_SUCCESS;
}
