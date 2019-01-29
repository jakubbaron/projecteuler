#include <iostream>
#include <limits>

// The series, 11 + 22 + 33 + ... + 1010 = 10405071317.
//
// Find the last ten digits of the series, 11 + 22 + 33 + ... + 10001000.
//
// https://www.mathblog.dk/project-euler-48-last-ten-digits/

int main(int argc, char** argv) {
  long result = 0;
  long modulo = 10000000000;
   
  for (int i = 1; i <= 1000; i++) {
    long temp = i;
    for (int j = 1; j < i; j++) {
      temp *= i;
      if(temp >= std::numeric_limits<long>::max() / 1000) {
        temp %= modulo;
      }
    }
  
    result += temp;
    result %= modulo;
  }
  std::cout << result << std::endl;

  return EXIT_SUCCESS;
}
