#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <cmath>

// A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
// 
// A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.
// 
// As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.
// 
// Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

auto get_divisors(int n) noexcept -> std::vector<int>{
  std::vector<int> divisors;
  for (int i = 1; i <= sqrt(n); i++)
  {
    if (n % i == 0)
    {
      divisors.emplace_back(i);
      const auto n_over_i = n / i;
      if (n_over_i != i) {
        divisors.emplace_back(n_over_i);
      }
    }
  }

  return divisors;
}

auto is_perfect_number(int n) noexcept -> bool {
  const auto divisors{get_divisors(n)};
  return std::accumulate(divisors.begin(), divisors.end(), -n) == n;
}

auto is_abundant_number(int n) noexcept -> bool {
  const auto divisors{get_divisors(n)};
  return std::accumulate(divisors.begin(), divisors.end(), -n) > n;
}

int main(int argc, char** argv) {
  static auto constexpr upper_bound = 28123;
  std::set<int> abundants;
  for(int i = 2; i < upper_bound; i++) {
    if(is_abundant_number(i)) {
      abundants.emplace(i);
    }
  }

  long long sum = 0LL;
  for(int i = 1; i <= upper_bound; i++) {
    bool sum_it_up = false;
    for(const auto& abundant: abundants) {
      int diff = i - abundant;
      if(diff <= 0) {
        sum_it_up = true;
        break;
      }
      if(abundants.count(diff)) {
        sum_it_up = false;    
        break;
      }
    }
    if(sum_it_up) {
      sum += i;
    }
  }

  std::cout << "sum of abundandts: " << std::accumulate(abundants.begin(), abundants.end(), 0) << std::endl;
  std::cout << "sum of all others: " << sum << std::endl;

  return EXIT_SUCCESS;
}
