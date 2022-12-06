#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::getline;
using ::std::pair;
using ::std::set;
using ::std::sort;
using ::std::stack;
using ::std::string;
using ::std::unordered_map;
using ::std::unordered_set;
using ::std::vector;

std::vector<int> split(const std::string &s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

int main(int argc, char *argv[]) {
  std::fstream my_file;
  my_file.open("day14.input", std::ios::in);
  unordered_map<char, unordered_map<char, char>> insertions;
  string polymer;
  if (!my_file) {
    std::cout << "No such file";
  } else {
    string line;
    getline(my_file, polymer);
    while (!my_file.eof()) {
      getline(my_file, line);
      if (line.empty()) continue;
      std::stringstream relation(line);
      std::string tag, insertion;
      getline(relation, tag, ' ');
      getline(relation, insertion, ' ');
      getline(relation, insertion);
      insertions[tag[0]][tag[1]] = insertion[0];
    }
  }

  unordered_map<char, unordered_map<char, unsigned long>> pair_frequencies;
  for (int i = 0; i < polymer.length() - 1; i++) {
    pair_frequencies[polymer[i]][polymer[i + 1]]++;
  }

  for (int i = 0; i < 40; i++) {
    cout << i << endl;
    unordered_map<char, unordered_map<char, unsigned long>> new_frequencies;
    for (const auto [first, val] : pair_frequencies) {
      for (const auto [second, freq] : val) {
        if (insertions.contains(first) && insertions[first].contains(second)) {
          char insert = insertions[first][second];
          new_frequencies[first][insert] += freq;
          new_frequencies[insert][second] += freq;
        }
      }
    }
    pair_frequencies = std::move(new_frequencies);
  }

  unordered_map<char, unsigned long> frequencies;
  for (const auto [first, val] : pair_frequencies) {
    for (const auto [second, freq] : val) {
      frequencies[first] += freq;
      frequencies[second] += freq;
    }
  }

  for (const auto [key, freq] : frequencies) {
    frequencies[key] = (freq + 1) / 2;
  }

  unsigned long min = LONG_MAX, max = 0;
  for (const auto [key, val] : frequencies) {
    if (val < min) min = val;
    if (val > max) max = val;
  }

  // (x + 1) / 2
  cout << "Diff: " << max - min << endl;

  my_file.close();
  return 0;
}
