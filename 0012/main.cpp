#include <iostream>
#include <vector>
#include <cmath>

// The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
// 
// 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
// 
// Let us list the factors of the first seven triangle numbers:
// 
//  1: 1
//  3: 1,3
//  6: 1,2,3,6
// 10: 1,2,5,10
// 15: 1,3,5,15
// 21: 1,3,7,21
// 28: 1,2,4,7,14,28
// We can see that 28 is the first triangle number to have over five divisors.
// 
// What is the value of the first triangle number to have over five hundred divisors?

const auto get_number_of_divisors(long long n) noexcept {
  auto divisors = 0;
  for (long long i = 1LL; i <= sqrt(n); i++)
  {
    if (n%i==0)
    {
      if (n/i == i) {
        divisors++;
      } else {
        divisors += 2;
      }
    }
  }

  return divisors;
}

int main(int argc, char** argv) {
  constexpr auto sought_divisors = 500;
  int num_of_divisors = 0;
  long long number = 0LL;
  long long sum = 0LL;

  while(num_of_divisors < sought_divisors) {
    number++;
    sum += number;
    num_of_divisors = get_number_of_divisors(sum);
  }

  std::cout << "Number: " << number << " Sum: " << sum << " number of divisors: " << num_of_divisors << std::endl;

  return EXIT_SUCCESS;
}
