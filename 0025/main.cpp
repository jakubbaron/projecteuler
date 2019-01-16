#include <iostream>
#include <queue>

// The Fibonacci sequence is defined by the recurrence relation:
//
// Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
// Hence the first 12 terms will be:
// 
// F1 = 1
// F2 = 1
// F3 = 2
// F4 = 3
// F5 = 5
// F6 = 8
// F7 = 13
// F8 = 21
// F9 = 34
// F10 = 55
// F11 = 89
// F12 = 144
// The 12th term, F12, is the first term to contain three digits.
// 
// What is the index of the first term in the Fibonacci sequence to contain 1000 digits?

auto fill_with_zeros = [](std::queue<int>& n1, std::queue<int>& n2) -> void { 
  if(n1.size() < n2.size()) {
    while(n1.size() < n2.size()) {
      n1.emplace(0);
    }
  } 
  if(n2.size() < n1.size()) {
    while(n2.size() < n1.size()) {
      n2.emplace(0);
    }
  } 

  return;
};

auto sum_of_two = [](std::queue<int>& n1, std::queue<int>& n2) -> std::queue<int> {
  fill_with_zeros(n1, n2);

  std::queue<int> n3;
  int carry_over = 0;
  while(!n1.empty()) {
    int sum = n1.front() + n2.front() + carry_over;
    n1.pop();
    n2.pop();
    carry_over = sum / 10;
    n3.emplace(sum % 10);
  }

  std::string str_carry_over{std::to_string(carry_over)};
  if(!str_carry_over.empty() && str_carry_over[str_carry_over.size() - 1] != '0') {
    for(int i = str_carry_over.size() - 1; i >= 0; i--) {
      n3.emplace(static_cast<int>(str_carry_over[i] - '0'));
    }
  }

  return n3;
};

auto fibonacci_with_number_of_digits(const int wanted_digits) noexcept -> int {
  std::queue<int> last_n_2;
  std::queue<int> last_n_1;
  last_n_2.emplace(0);
  last_n_1.emplace(1);

  int index = 1;
  int number_of_digits = 0;
  while(number_of_digits < wanted_digits) {
    auto copy_of_n_1 = last_n_1;
    auto current_element = sum_of_two(last_n_2, last_n_1);

    number_of_digits = current_element.size();
    index++;

    last_n_2 = std::move(copy_of_n_1);
    last_n_1 = std::move(current_element);
  }

  return index;
}
int main(int argc, char** argv) {
  std::cout << fibonacci_with_number_of_digits(1000) << std::endl;
  return EXIT_SUCCESS;
}
