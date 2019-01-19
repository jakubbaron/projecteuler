#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <vector>

// Euler discovered the remarkable quadratic formula:
// 
// n2+n+41
// It turns out that the formula will produce 40 primes for the consecutive integer values 0≤n≤39. However, when n=40,402+40+41=40(40+1)+41 is divisible by 41, and certainly when n=41,412+41+41 is clearly divisible by 41.
// 
// The incredible formula n2−79n+1601 was discovered, which produces 80 primes for the consecutive values 0≤n≤79. The product of the coefficients, −79 and 1601, is −126479.
// 
// Considering quadratics of the form:
// 
// n2+an+b, where |a|<1000 and |b|≤1000
// 
// where |n| is the modulus/absolute value of n
// e.g. |11|=11 and |−4|=4
// Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n=0.

auto is_prime(int n) noexcept -> bool {
  for(int i = 2; i < sqrt(n) + 1; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

auto n_primes(int n) noexcept -> const std::set<int> {
    std::set<int> primes;
    int candidate = 2;
    primes.emplace(candidate);

    int count = 1;
    while(count < n) {
      candidate++;
      if(is_prime(candidate)) {
        primes.emplace(candidate);
        count++;
      }
    }

    return primes;
}

auto find_best_coefficients() noexcept -> const std::pair<int, int> {
  int a(0), b(0);
  while(std::abs(a) < 1000 && std::abs(b) <= 1000) {

  }
  return std::make_pair(a,b);
}

int main(int argc, char** argv) {
  static auto constexpr how_many_primes = 10000;
  std::set<int> primes = n_primes(how_many_primes);

  return EXIT_SUCCESS;
}
