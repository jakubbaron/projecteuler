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

struct best_coefficients {
  int a;
  int b;
  int n;
};

auto formula = [](const int a, const int b, const int n) {
  return n * n + a * n + b;
};

auto find_best_coefficients() noexcept -> best_coefficients {
  auto best = best_coefficients();
  best.a = 0;
  best.b = 0;
  best.n = 0;

  static auto constexpr how_many_primes = 50000;
  std::set<int> primes = n_primes(how_many_primes);

  for(int a = -1000; a <= 1000; a++) {
    for(int b = -1000; b <= 1000; b++) {
      bool broken_consecutiveness = false;
      int n = 0;
      while(!broken_consecutiveness) {
        if(!primes.count(formula(a, b, n))) {
          broken_consecutiveness = true;
        }
        n++;
      }
      if(best.n < n) {
        best.n = n;
        best.a = a;
        best.b = b;
      }
    }
  }

  return best;
}

int main(int argc, char** argv) {
  const auto best = find_best_coefficients();
  std::cout << "a: " << best.a << " b: " << best.b << " n: " << best.n << std::endl;
  return EXIT_SUCCESS;
}
