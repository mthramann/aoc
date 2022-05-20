#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::getline;
using ::std::map;
using ::std::optional;
using ::std::ostream;
using ::std::pair;
using ::std::priority_queue;
using ::std::queue;
using ::std::set;
using ::std::sort;
using ::std::stack;
using ::std::string;
using ::std::tuple;
using ::std::unique_ptr;
using ::std::unordered_map;
using ::std::unordered_set;
using ::std::vector;

std::vector<int> split(const std::string& s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

struct Die {
  int next = 1;

  int num_rolls = 0;

  int roll() {
    num_rolls++;
    if (next == 100) {
      next = 1;
      return 100;
    }
    return next++;
  }
};

void move(int& curr, int roll) {
  roll = roll % 10;
  if (roll + curr > 10) {
    roll -= 10;
  }
  curr += roll;
}

// Position and score pair.
typedef pair<int, int> Player;

int main(int argc, char* argv[]) {
  // std::fstream my_file;
  // my_file.open("day20.input", std::ios::in);
  // if (!my_file) {
  //   std::cout << "No such file";
  // } else {
  //   getline(my_file, conversion_key);
  //   string line;
  //   while (!my_file.eof()) {
  //     getline(my_file, line);
  //     if (line.empty()) continue;

  //   }
  // }

  set<pair<int, int>> die;
  die.insert({3, 1});
  die.insert({4, 3});
  die.insert({5, 6});
  die.insert({6, 7});
  die.insert({7, 6});
  die.insert({8, 3});
  die.insert({9, 1});

  unsigned long long p1_universes = 0, p2_universes = 0;

  map<Player, map<Player, unsigned long long>> frequencies;
  frequencies[{8, 0}][{10, 0}] = 1;

  while (!frequencies.empty()) {
    map<Player, map<Player, unsigned long long>> new_frequencies;
    for (auto [p1, subfreq] : frequencies) {
      for (auto [p2, freq] : subfreq) {
        for (auto [p1roll, p1splits] : die) {
          Player new_p1 = p1;
          move(new_p1.first, p1roll);
          new_p1.second += new_p1.first;
          if (new_p1.second >= 21) {
            p1_universes += freq * p1splits;
            continue;
          }
          for (auto [p2roll, p2splits] : die) {
            Player new_p2 = p2;
            move(new_p2.first, p2roll);
            new_p2.second += new_p2.first;
            if (new_p2.second >= 21) {
              p2_universes += freq * p1splits * p2splits;
              continue;
            }
            new_frequencies[new_p1][new_p2] += freq * p1splits * p2splits;
          }
        }
      }
    }
    frequencies = std::move(new_frequencies);
  }

  cout << p1_universes << endl << p2_universes << endl;

  //  my_file.close();
  return 0;
}
