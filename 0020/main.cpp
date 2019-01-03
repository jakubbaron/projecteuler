#include <iostream>
#include <queue>

// n! means n × (n − 1) × ... × 3 × 2 × 1
// 
// For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
// and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
// 
// Find the sum of the digits in the number 100!
using Number = std::queue<int>;

auto get_sum_of_digits = [](Number numbers) {
  long long sum = 0LL;

  while(!numbers.empty()) {
    const auto digit = numbers.front();
    sum += digit;
    numbers.pop();
  }

  return sum;
};

const auto int_to_number(const int val) {
  std::string str_val = std::to_string(val);
  Number number;
  for(int i = str_val.size() - 1; i >= 0; i--) {
    number.emplace(static_cast<int>(str_val[i] - '0'));
  }
  return number;
}

const auto multiply(Number number, const int base, const int extra_zeroes = 0) noexcept {
  Number result;
  for(int i = 0; i < extra_zeroes; i++) {
    result.emplace(0);
  }
  int carry_over = 0;

  while(!number.empty()) {
    auto digit = number.front();
    number.pop();
    digit *= base;
    digit += carry_over;
    carry_over = digit / 10;
    result.emplace(digit % 10);
  }
  std::string str_carry_over{std::to_string(carry_over)};
  if(!str_carry_over.empty() && str_carry_over[str_carry_over.size() - 1] != '0') {
    for(int i = str_carry_over.size() - 1; i >= 0; i--) {
      result.emplace(static_cast<int>(str_carry_over[i] - '0')); 
    }
  }

  return result;
}

const auto display_result(Number result) noexcept {
  while(!result.empty()) {
    auto digit = result.front();
    result.pop();
    std::cout << digit << " ";
  }
  std::cout << std::endl;
}

const auto multiply(Number first, Number second) noexcept {
  Number final_result;
  std::vector<Number> helper;
  int zero_counter = 0;
  while(!second.empty()) {
    const auto multiplier = second.front();
    second.pop();
    helper.emplace_back(multiply(first, multiplier, zero_counter));
    zero_counter++;
  }

  int carry_over = 0;
  bool finished = false;
  while(!finished) {
    finished = true;
    int digit = carry_over;
    for(auto& current: helper) {
      finished &= current.empty();
      if(current.empty()) {
        continue;
      }
      const auto value = current.front();
      current.pop();
      digit += value;
    }

    if(finished) {
      break;
    }

    carry_over = digit / 10;
    final_result.emplace(digit % 10);
  }

  std::string str_carry_over{std::to_string(carry_over)};
  if(!str_carry_over.empty() && str_carry_over[str_carry_over.size() - 1] != '0') {
    for(int i = str_carry_over.size() - 1; i >= 0; i--) {
      final_result.emplace(static_cast<int>(str_carry_over[i] - '0')); 
    }
  }
   
  return final_result;
}

int main(int argc, char** argv) {
  constexpr auto fact = 100;
  Number number = int_to_number(1);

  for(int i = 1; i <= fact; i++) {
    number = multiply(number, int_to_number(i));
  }

  std::cout << "Sum of the digits is: " << get_sum_of_digits(number) << std::endl;

  return EXIT_SUCCESS;
}
