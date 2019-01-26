#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>
#include <cmath>

// An irrational decimal fraction is created by concatenating the positive integers:
// 
// 0.123456789101112131415161718192021...
// 
// It can be seen that the 12th digit of the fractional part is 1.
// 
// If dn represents the nth digit of the fractional part, find the value of the following expression.
// 
// https://www.mathblog.dk/project-euler-40-digit-fractional-part-irrational-number/
// d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
//
// 1-9: 1-9
// 10-99: 10-189
// 100-999: 190-2.889
// 1.000-9.999:  2.890-38.889
// 10.000-99.999: 38.890 – 488.889
// 100.000-999.999: 488.890 – 5.888.889
// 
// As an example I will start with finding d1000. We are in the 100-999 range so we deduct 189 which  is the starting point of that number. Which gives us 1000-189 = 811. Each number is 3 dgits, so we are at number 811/3 + 99 = 369 with 1/3 left over. So the digit we are looking for is 1/3 into 370, meaning the first digit of 370 => 3
// 
// So with the given example, I think we are ready to plow through the 7 digits we need to find for the solution:
// 
// d1 :  1/1 + 0 = 1 => 1
// 
// d10 :  (10-9)/2 + 9 = 9 1/2 => 1
// 
// d100 :  (100-9)/2 + 9 = 54 1/2 => 5
// 
// d1.000 :  (1.000-189)/3 + 99 = 369 1/3 => 3
// 
// d10.000 :  (10.000 – 2.889) / 4 + 999 = 2776 3/4 => 7
// 
// d100.000 :  (100.000 – 38.889) /5 + 9.999 = 22.221 1/5 => 2
// 
// d1.000.000 :  (1.000.000 – 488.889)/6 + 99.999  = 185.184 1/6 => 1
// 
// So the result is 1153721 = 210

struct Digits {
  auto add_digit(const char c) noexcept -> void {
    vec.emplace_back(static_cast<int>(c - '0'));
  }
  auto get_product() const noexcept -> int {
    int product = 1;
    for(const auto& item: vec) {
      product *= item;
    }
    return product;
  }

  std::vector<int> vec;
};

int main(int argc, char** argv) {
  std::ostringstream ss;
  int i = 0;
  while(ss.tellp() <= 1000*1000) {
    ss << std::to_string(i++);
  }
  std::string str{ss.str()};
  Digits d;
  for(int i = 0; i <= 6; i++) {
    d.add_digit(str[std::pow(10, i)]);
  }
  std::cout << "Sum: " << d.get_product() << std::endl;

  return EXIT_SUCCESS;
}
