#include <iostream>
#include <numeric>

// The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.
// 
// We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
// 
// There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.
// 
// If the product of these four fractions is given in its lowest common terms, find the value of the denominator.

// https://en.cppreference.com/w/cpp/numeric/gcd
// https://www.mathblog.dk/project-euler-33-fractions-unorthodox-cancelling-method/

auto denominator_of_non_trivial_examples() noexcept -> int {
  int denproduct = 1;
  int nomproduct = 1;
  
  for (int i = 1; i < 10; i++) {
    for (int den = 1; den < i; den++) {
      for (int nom = 1; nom < den; nom++) {
        if ((nom * 10 + i) * den == nom * (i * 10 + den)) {
          denproduct *= den;
          nomproduct *= nom;
        }
      }
    }
  }
  denproduct /= std::gcd(nomproduct, denproduct);
  return denproduct;
}

int main(int argc, char** argv) {
  std::cout << "Denominator: " << denominator_of_non_trivial_examples() << std::endl;
  return EXIT_SUCCESS;
}
