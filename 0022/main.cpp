#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
// 
// For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
// 
// What is the total of all the name scores in the file?

auto name_worth = [](const std::string& name) -> uint32_t {
  uint32_t score = 0;
  for(const auto& c: name) {
    score += static_cast<uint32_t>(c - 'A' + 1);
  } 
  return score;
};

int main(int argc, char** argv) {
  std::ifstream infile("names.txt");
  std::string name;
  std::vector<std::string> names;
  while (std::getline(infile, name, ',')) {
    name.erase(std::remove(name.begin(), name.end(), '\"' ), name.end());
    names.emplace_back(name);
  }
  std::sort(names.begin(), names.end());
  unsigned long long over_all_score = 0ULL;
  for(size_t i = 0; i < names.size(); i++) {
    over_all_score += static_cast<unsigned long long>(name_worth(names[i]) * (i + 1));
    //std::cout << "[" << i << "] Current score: " << over_all_score << std::endl;
  }
  std::cout << "Overall score: " << over_all_score << std::endl;
  return EXIT_SUCCESS;
}
