#include <iostream>
#include <vector>
#include <cmath>

// The first two consecutive numbers to have two distinct prime factors are:
// 
// 14 = 2 × 7
// 15 = 3 × 5
// 
// The first three consecutive numbers to have three distinct prime factors are:
// 
// 644 = 2² × 7 × 23
// 645 = 3 × 5 × 43
// 646 = 2 × 17 × 19.
// 
// Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?
// https://www.mathblog.dk/project-euler-47-distinct-prime-factors/
//
int NumberOfPrimeFacors(int number, const std::vector<int>& primes) {
  int nod = 0;
  bool pf;
  int remain = number;

  for (int i = 0; i < primes.size(); i++) {
    // In case there is a remainder this is a prime factor as well
    // The exponent of that factor is 1
    if (primes[i] * primes[i] > number) {
        return ++nod;
    }

    pf = false;
    while (remain % primes[i] == 0) {
        pf = true;
        remain = remain / primes[i];
    }
    if (pf){
        nod++;
    }

    //If there is no remainder, return the count
    if (remain == 1) {
        return nod;
    }
  }
  return nod;
}

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

int main(int argc, char** argv) {
  const auto primes = primes_below(100000);
  int targetpf = 4;
  int targetConsec = 4;
  int consec = 1;
  int result = 2 * 3 * 5 *7;
  std::vector<int> conseq_vec;
  
  while (consec < targetConsec) {
    result++;
    if (NumberOfPrimeFacors(result, primes) >= targetpf) {
      consec++;
      conseq_vec.emplace_back(result);
    } else {
      consec = 0;
      conseq_vec.clear();
    }
  }

  for(const auto& item: conseq_vec) {
    std::cout << item << std::endl;
  }

  return EXIT_SUCCESS;
}
