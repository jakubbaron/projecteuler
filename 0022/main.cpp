#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
// 
// For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
// 
// What is the total of all the name scores in the file?

int main(int argc, char** argv) {
  std::ifstream infile("names.txt");
  std::string name;
  std::vector<std::string> names;
  while (std::getline(infile, name)) {
    names.emplace_back(name);
  }
  for(const auto& name: names) {
    std::cout << name << std::endl; 
  }

  return EXIT_SUCCESS;
}
