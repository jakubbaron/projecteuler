#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

// The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:
// 
// 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
// 
// By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.
// 
// Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?

constexpr auto triangle_number(const int n) noexcept -> int {
  return n * (n + 1) / 2;
}

auto triangle_numbers(const int n) noexcept -> std::unordered_set<int> {
  std::unordered_set<int> t;
  for(int i = 1; i <= n; i++) {
    t.emplace(triangle_number(i));
  }
  return t;
}

auto string_to_value(const std::string& str) noexcept -> int {
  int sum = 0;
  for(const auto& c: str) {
    sum += static_cast<int>(c - 'A' + 1);
  }
  return sum;
}

int main(int argc, char** argv) {
  std::ifstream infile("words.txt");
  std::vector<std::string> words;
  {
    std::string word;
    while (std::getline(infile, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\"' ), word.end());
      words.emplace_back(word);
    }
  }

  size_t count = 0;
  const auto triangles = triangle_numbers(100);
  for(const auto& word: words) {
    if(triangles.count(string_to_value(word))) {
      count++;
    }
  }
  std::cout << "Triangle words count: " << count << std::endl;

  return EXIT_SUCCESS;
}
