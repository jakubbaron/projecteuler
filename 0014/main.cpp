#include <iostream>

// The following iterative sequence is defined for the set of positive integers:
// 
// n → n/2 (n is even)
// n → 3n + 1 (n is odd)
// 
// Using the rule above and starting with 13, we generate the following sequence:
// 
// 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
// It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
// Although it has not been proved yet (Collatz Problem), it is thought that all starting
// numbers finish at 1.
// 
// Which starting number, under one million, produces the longest chain?
// 
// NOTE: Once the chain starts the terms are allowed to go above one million.

const auto is_even = [](const long value) {
  return !(value & 1L);
};

const auto next_sequenece_element = [](const long n){ 
  if(n == 1L) {
    return 0L;
  }

  return is_even(n) ? n / 2L : (3L * n + 1L); 
};

const auto get_sequence_length = [](long n) {
  auto counter = 0;
  while(n != 0L) {
    n = next_sequenece_element(n);
    counter++;
  }
  return counter;
};

const auto get_longest_sequence_number = [](const auto upper_bound) {
  auto longest_sequence = 0;
  auto number = upper_bound;
  for(auto current = upper_bound; current >= 0; current--) {
    const auto current_seq_length = get_sequence_length(current);
    if(longest_sequence < current_seq_length) {
      longest_sequence = current_seq_length;
      number = current;
    }
  }
  return std::make_pair(number, longest_sequence);
};

int main(int argc, char** argv) {
  const auto result = get_longest_sequence_number(1000L * 1000L);
  std::cout << "Length of sequence: " << result.first << " length " << result.second << std::endl;
  return EXIT_SUCCESS;
}
