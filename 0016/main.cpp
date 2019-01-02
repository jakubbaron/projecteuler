#include <iostream>
#include <queue>

// 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

// What is the sum of the digits of the number 2^1000?

using Result = std::queue<int>;

auto get_sum_of_digits = [](Result numbers) {
  long long sum = 0LL;

  while(!numbers.empty()) {
    const auto digit = numbers.front();
    sum += digit;
    numbers.pop();
  }

  return sum;
};

const auto multiply(Result& result, const int base) noexcept {
  Result helper;
  int carry_over = 0;

  while(!result.empty()) {
    auto digit = result.front();
    result.pop();
    digit *= base;
    digit += carry_over;
    carry_over = digit / 10;
    helper.emplace(digit % 10);
  }
  std::string str_carry_over{std::to_string(carry_over)};
  if(!str_carry_over.empty() && str_carry_over[str_carry_over.size() - 1] != '0') {
    for(int i = str_carry_over.size() - 1; i >= 0; i--) {
      helper.emplace(static_cast<int>(str_carry_over[i] - '0')); 
    }
  }

  return helper;
}

const auto pow_stack(const int base, int exp) noexcept {
  Result result;
  result.emplace(1);

  while(exp > 0) {
    result = multiply(result, base);
    exp--;
  }

  return result;
}

const auto display_result(Result result) noexcept {
  while(!result.empty()) {
    auto digit = result.front();
    result.pop();
    std::cout << digit << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  constexpr auto exp = 1000;
  constexpr auto base = 2;

  std::cout << "Sum of the digits is: " << get_sum_of_digits(pow_stack(base, exp)) << std::endl;

  return EXIT_SUCCESS;
}
