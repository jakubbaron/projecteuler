#include <iostream>

// The prime factors of 13195 are 5, 7, 13 and 29.
// What is the largest prime factor of the number 600851475143 ?

// https://www.geeksforgeeks.org/find-largest-prime-factor-number/

constexpr auto max_prime_factors(long long n) 
{ 
    // Initialize the maximum prime factor 
    // variable with the lowest one 
    long long maxPrime = -1; 

    while (!(n & 1)) {  // is_even
      maxPrime = 2;
      n >>= 1;  // /= results in that it can't be a constepxr, possible infinite loop
    }
  
    // n must be odd at this point, thus skip 
    // the even numbers and iterate only for 
    // odd integers 
    for (int i = 3; i <= n / 3; i += 2) { 
        while (n % i == 0) { 
            maxPrime = i; 
            n = n / i; 
        } 
    } 
  
    // This condition is to handle the case 
    // when n is a prime number greater than 2 
    if (n > 2) 
        maxPrime = n; 
  
    return maxPrime; 
} 

int main(int argc, char** argv) {
  //constexpr auto input = 13195;
  constexpr auto input = 600851475143;
  constexpr auto result = max_prime_factors(input);
  std::cout << "Answer: " << result << std::endl;
  return EXIT_SUCCESS;
}
