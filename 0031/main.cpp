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

auto how_many_ways_for_pounds(const unsigned int pounds) noexcept -> size_t {
  unsigned int pences = pounds * 100;
  static std::vector<unsigned int> coins = {200, 100, 50, 20, 5, 2, 1}; 
  std::map<unsigned int, unsigned int> available_coins = {
    {200, pences/200},
    {100, pences/100},
    {50, pences/50},
    {20, pences/20},
    {5, pences/5}, 
    {2, pences/2},
    {1, pences/1}
  };

//  for(const auto& item: available_coins) {
//    std::cout << item.first << " " << item.second << std::endl; 
//  }

  size_t ways = 0;
  while(!available_coins.empty()) {
    auto needed_pences = pences;  
    for(const auto& coin: coins) {
      std::cout << "Testing coin[" << coin << "] needed pences [" << needed_pences << "] ways[" << ways << "]" << std::endl;
      auto coin_it = available_coins.find(coin);
      if(coin_it == available_coins.end()) {
        std::cout << "Coin[" << coin << "] no longer available" <<  std::endl;
        continue;
      }

      auto amount_of_coins = coin_it->second;
      //std::cout << (coin * amount_of_coins) << " " << needed_pences << " " << amount_of_coins << std::endl;
      while(coin <= needed_pences && amount_of_coins > 0) {
        needed_pences -= coin; 
        amount_of_coins--;
        std::cout << "Coin[" << coin << "] needed pences [" << needed_pences << "] left coins availavle[" << amount_of_coins << "]" << std::endl;
      } 

      if((needed_pences == 0 && amount_of_coins == 0)/* || (coin > needed_pences)*/) {
        available_coins[coin]--;
        if(available_coins[coin] == 0) {
          std::cout << "Out of [" << coin << "] coins" << std::endl;
          available_coins.erase(coin);
        }
      }

      if(needed_pences == 0) {
        ways++;
        break;
      }
    }
    if(available_coins[100] > 0 && available_coins[50] != 4) {
      for(const auto& item: available_coins) {
        std::cout << item.first << " " << item.second << std::endl; 
      }
      break;
    }
  }
  return ways;
}

int main(int argc, char** argv) {
  std::cout << "Ways to made 2 pounds: " << how_many_ways_for_pounds(2) << std::endl; 
  return EXIT_SUCCESS;
}
