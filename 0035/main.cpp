#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

// The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
// 
// There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
// 
// How many circular primes are there below one million?

auto string_to_int(const std::string& str) noexcept -> uint32_t {
  // normally we'd check if there are only 0-9 characters, but we assume that
  // we don't pass anything 'evil'
  uint32_t out = 0;
  static const std::vector<uint32_t> pows = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
  for(int i = 0; i < str.length(); i++) {
    out += static_cast<uint32_t>(str[i] - '0') * pows[str.length() - i - 1];
  }

  return out;
}

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
    for(int candidate = 2; candidate < n; candidate++) {
      if(is_prime(candidate)) {
        primes.emplace(candidate);
      }
    }

    return primes;
}
auto is_circular(int number, const std::set<int>& primes) noexcept -> bool {
  std::string s = std::to_string(number);
  for(int i = 0; i < s.size() - 1; i++) {
    std::rotate(s.begin(), s.begin() + 1, s.end());
    if(!primes.count(string_to_int(s))) {
      return false;
    }
  }

  return true;
}

auto count_circular_primes_below(int n) noexcept -> size_t { 
  static auto primes(primes_below(n));
  size_t count = 0;
  for(const auto& prime: primes) {
    if(is_circular(prime, primes)) {
      //std::cout << "Circular prime: " << prime << std::endl;
      count++;
    }
  }
  return count;
}

int main(int argc, char** argv) {
  static constexpr auto upper_bound = 1000*1000;
  const auto result = count_circular_primes_below(upper_bound);
  std::cout << "Number of circular items below[" << upper_bound <<"]: " << result << std::endl;
  return EXIT_SUCCESS;
}
