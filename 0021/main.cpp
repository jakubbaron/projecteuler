#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <numeric>

// Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
// If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
// 
// For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
// 
// Evaluate the sum of all the amicable numbers under 10000.

auto get_divisors(long long n) noexcept -> std::vector<int>{
  std::vector<int> divisors;
  for (long long i = 1LL; i <= sqrt(n); i++)
  {
    if (n%i==0)
    {
      divisors.emplace_back(i);
      const auto n_over_i = n/i;
      if (n_over_i != i) {
        divisors.emplace_back(n_over_i);
      }
    }
  }

  return divisors;
}

auto check_for_amitable_number(int number) noexcept -> std::pair<bool, int> {
  const auto divisors = get_divisors(number);
  const auto sum_of_divisors = std::accumulate(divisors.begin(), divisors.end(), -number);
  const auto divisors_of_sum = get_divisors(sum_of_divisors);
  const auto sum_of_divisors_of_sum = std::accumulate(divisors_of_sum.begin(), divisors_of_sum.end(), -sum_of_divisors); 

  bool is_amicable = (number == sum_of_divisors_of_sum && number != sum_of_divisors);
  return std::make_pair(is_amicable, sum_of_divisors);
}

int main(int argc, char** argv) {
  static auto constexpr UPPER_BOUND = 10000;
  std::set<int> amicable_numbers;
  for(int i = 1; i< UPPER_BOUND; i++) {
    // We might get some numbers before i hits them as per example
    if(amicable_numbers.count(i)) {
      continue;
    }

    const auto result = check_for_amitable_number(i);
    if(result.first) {
      amicable_numbers.insert(i); 
      amicable_numbers.insert(result.second); 
      std::cout << i << " is an amicable number, as well as: " << result.second << std::endl;
    }
  }
  
  std::cout << "Sum of amicable numbers till " << UPPER_BOUND << " is: " << std::accumulate(amicable_numbers.begin(), amicable_numbers.end(), 0) << std::endl;

  return EXIT_SUCCESS;
}
