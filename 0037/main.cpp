#include <iostream>
#include <set>
#include <vector>
#include <cmath>

// The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
// 
// Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
// 
// NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

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
    for(int candidate = 2; candidate <= n; candidate++) {
      if(is_prime(candidate)) {
        primes.emplace(candidate);
      }
    }

    return primes;
}

auto is_truncatable_prime(const int prime, const std::set<int>& primes) noexcept -> bool {
  std::string str_prime = std::to_string(prime);
  for(int i = 1; i < str_prime.size(); i++) {
    // std::cout << string_to_int(str_prime.substr(0, i)) << " " << string_to_int(str_prime.substr(i)) << std::endl;
    if(!primes.count(string_to_int(str_prime.substr(0, i))) || !primes.count(string_to_int(str_prime.substr(i)))) {
      return false;
    } 
  }

  return true;
}

auto sum_of_trunstable_primes() noexcept -> size_t {
  size_t sum = 0;
  size_t count = 0;
  static constexpr auto upper_bound = 1000*1000;
  auto primes = primes_below(upper_bound);
  const std::set<int> skip_primes = {2, 3, 5, 7};
  for(const auto& prime: primes) {
    if(skip_primes.count(prime)) {
      continue;
    }
    if(is_truncatable_prime(prime, primes)) {
      sum += prime;
      count++;
    }
  }
  if(count != 11) {
    //lame check
    return 0;
  }

  return sum;
}


int main(int argc, char** argv) {
  // std::cout << "Is truncatable: " << is_truncatable_prime(3797, primes_below(3797));
  std::cout << sum_of_trunstable_primes() << std::endl;
  return EXIT_SUCCESS;
}
