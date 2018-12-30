#include <iostream>
#include <cmath>

// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13,
// we can see that the 6th prime is 13.
//
// What is the 10 001st prime number?

auto is_prime(int n) noexcept {
  for(int i = 2; i < sqrt(n) + 1; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

auto nth_prime(int n) noexcept {
    int candidate = 2;
    int count = 1;
    while(count < n) {
      candidate++;
      if(is_prime(candidate)) {
        count++;
      }
    }

    return candidate;
}


int main(int argc, char** argv) {
  constexpr auto which_prime = 10001;
  std::cout << "Nth prime is: " << nth_prime(which_prime) << std::endl;
  return EXIT_SUCCESS;
}
