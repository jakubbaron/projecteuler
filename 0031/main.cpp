#include <iostream>
#include <map>
#include <vector>
#include <set>

// In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
//
//1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
//It is possible to make £2 in the following way:
//
//1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
//How many different ways can £2 be made using any number of coins?

// https://www.mathblog.dk/project-euler-31-combinations-english-currency-denominations/

// we actually just need to count in how many ways we can build each of the
// coin's value

// Let's start with 5p
// 2p can be made in 2 ways:
// 1x2p 0x1p
// 0x2p 2x1p
// 5p can be made in 4 ways:
// 1x5p 0x2p 0x1p
// 0x5p 2x2p 1x1p
// 0x5p 1x2p 3x1p
// 0x5p 0x2p 5x1p
// 10p can be made in 11 ways:
// 1x10p 0x5p 0x2p 0x1p
// 0x10p 2x5p 0x2p 0x1p
// 0x10p 1x5p 2x2p 1x1p
// 0x10p 1x5p 1x2p 3x1p
// 0x10p 1x5p 0x2p 5x1p
// 0x10p 0x5p 5x2p 0x1p
// 0x10p 0x5p 4x2p 2x1p
// 0x10p 0x5p 3x2p 4x1p
// 0x10p 0x5p 2x2p 6x1p
// 0x10p 0x5p 1x2p 8x1p
// 0x10p 0x5p 0x2p 10x1p

auto how_many_ways_for_pounds(const unsigned int pences) noexcept -> size_t {
  static const std::vector<unsigned int> coins = { 1, 2, 5, 10, 20, 50, 100, 200 };
  if(coins.size() != 8) {
    std::cerr << "Wrong coins size" << std::endl;
    return 0;
  }

  std::vector<unsigned int> ways(static_cast<size_t>(pences + 1), 0);
  ways[0] = 1;

  for(int i = 0; i < coins.size(); i++) {
    for(int j = coins[i]; j <= pences; j++) {
      ways[j] += ways[j - coins[i]];
    }
  }

  return ways[pences];
}

int main(int argc, char** argv) {
  std::cout << "Ways to made 2 pounds: " << how_many_ways_for_pounds(200) << std::endl; 
  return EXIT_SUCCESS;
}
