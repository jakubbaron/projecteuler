#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <iomanip>
// Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
using IntVec = std::vector<int>;
using IntStack = std::stack<int>;
using Numbers = std::vector<IntVec>;

const auto print_numbers(const Numbers& numbers) noexcept {
  for(const auto& number: numbers) {
    for(const auto& digit: number) {
      std::cout << digit;
    }
    std::cout << std::endl;
  }
}

const auto read_int_vector(const std::string& line) noexcept {
  IntVec vec;
  for(int i = 0; i < line.size(); i++) {
    vec.emplace_back(static_cast<int>(line[i] - '0'));
  }

  return vec;
}

const auto read_all_numbers(std::ifstream& infile) noexcept {
  Numbers numbers;
  std::string line;
  while (std::getline(infile, line)) {
    numbers.emplace_back(read_int_vector(line)); 
  }

  return numbers;
}

const auto sum_numbers(const Numbers& numbers) noexcept {
  IntStack sum;
  if(numbers.empty()) {
    return sum;
  }

  const auto number_of_digits = numbers[0].size();
  int carry_over = 0;
  for(int idx = number_of_digits - 1; idx >= 0; idx--) {
    auto current_sum = carry_over;
    for(const auto& number: numbers) {
      current_sum += number.at(idx); 
    }
    sum.emplace(current_sum % 10);
    carry_over = current_sum / 10;
  }
  std::string str_carry_over = std::to_string(carry_over);
  for(int i = str_carry_over.size() - 1; i >= 0; i--) {
    sum.emplace(static_cast<int>(str_carry_over[i] - '0'));
  }
  return sum;
}

int main(int argc, char** argv) {
  std::ifstream infile("input.txt");
  constexpr auto sought_numbers = 10;
  const auto numbers = read_all_numbers(infile);
  auto sum = sum_numbers(numbers);
  if(sum.size() < sought_numbers) {
    while(!sum.empty()) {
      std::cout << sum.top();
      sum.pop();
    }
  } else {
    for(int i = 0; i < sought_numbers; i++) {
      std::cout << sum.top();
      sum.pop();
    }
  }

  std::cout << std::endl;
  return EXIT_SUCCESS;
}
