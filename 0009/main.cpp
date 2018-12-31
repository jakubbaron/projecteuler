#include <iostream>
#include <vector>

// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
//
// a^2 + b^2 = c^2
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
//
// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.


auto is_thousand_triplet = [](const auto val1, const auto val2, const auto val3) {
  return (val1 + val2 + val3) == 1000;
};

auto is_valid_pythagorean_triplet = [](const int val1, const int val2, const int val3){
  return (val1 < val2) && (val2 < val3) && (((val1 * val1) + (val2 * val2)) == (val3 * val3));
};

//auto is_valid_pythagorean_triplet_vec = [](const std::vector<int> vals){
//  return (vals.size() == 3 && is_valid_pythagorean_triplet(vals[0], vals[1], vals[2])); 
//};

constexpr auto find_triplet(const int max_val) noexcept {
  for(int i = 1; i <= max_val; i++) {
    for(int j = i + 1; j <= max_val; j++) {
      for(int k = j + 1; k <= max_val; k++) {
        if(!is_valid_pythagorean_triplet(i, j, k)) {
          continue;
        }        
        //std::cout << "Checking: " << i << " " << j << " " << k << std::endl;
        if(is_thousand_triplet(i, j, k)) {
          std::cout << "Found the triplet: " << i << " " << j << " " << k << std::endl;
          std::cout << "Product is: " << (i * j * k) << std::endl; 
          return true;
        }
      }
    }
  }
  return false;
}

int main(int argc, char** argv) {
  //std::cout << "Is valid: " << is_valid_pythagorean_triplet(3,4,5) << std::endl;
  //std::cout << "Is valid: " << is_valid_pythagorean_triplet_vec({3,4,5}) << std::endl;
  
  // It can't ba a thousand as 1 + 2 + 997 = 1000, so the last thing that we
  // can look for. IT's not a Pythagorean triplet, but that the last sensible
  // value to check
  constexpr auto max_val = 997;
  find_triplet(max_val);
  return EXIT_SUCCESS;
}
