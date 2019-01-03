#include <iostream>
#include <map>
#include <string>

// If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
// 
// If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
// 
// NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.

int main(int argc, char** argv) {
  static const std::map<int, std::string> teens = {
    {11, "eleven"},
    {12, "twelve"},
    {13, "thirteen"},
    {14, "fourteen"},
    {15, "fifteen"},
    {16, "sixteen"},
    {17, "seventeen"},
    {18, "eighteen"},
    {19, "nineteen"}
  };

  static const std::map<int, std::string> tens = {
    {1, "ten"},
    {2, "twenty"},
    {3, "thirty"},
    {4, "forty"},
    {5, "fifty"},
    {6, "sixty"},
    {7, "seventy"},
    {8, "eighty"},
    {9, "ninety"}
  };

  static const std::map<int, std::string> singles = {
    {1, "one"},
    {2, "two"},
    {3, "three"},
    {4, "four"},
    {5, "five"},
    {6, "six"},
    {7, "seven"},    
    {8, "eight"},
    {9, "nine"}
  };

  constexpr auto upper_bound = 1000;

  const auto HUNDRED_SIZE = std::string{"hundred"}.size();
  const auto AND_SIZE = std::string{"and"}.size();
  int sum = 0;
  for(int i = 1; i <= upper_bound; i++) {
    int number = i;
    if(number == 1000) {
      sum += std::string{"onethousand"}.size();
      continue;
    }
    const auto hundreds_no = number / 100;
    if(number / 100 > 0) {
      sum += singles.at(hundreds_no).size();
      sum += HUNDRED_SIZE;
    }

    number = number % 100;
    
    if(number > 0 && hundreds_no) {
      sum += AND_SIZE;
    }

    const auto tens_no = number / 10;
    const auto last_digit = number % 10;
    if(tens_no == 0 && last_digit == 0) {
      continue;
    } else if(last_digit == 0) {
      sum += tens.at(tens_no).size();      
    } else if(tens_no == 1) {
      sum += teens.at(number).size();
    } else if(tens_no == 0) {
      sum += singles.at(last_digit).size();
    } else {
      sum += singles.at(last_digit).size();
      sum += tens.at(tens_no).size();
    }
  }

  std::cout << "Total number of characters: " << sum << std::endl;
  return EXIT_SUCCESS;
}
