#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::set;
using ::std::sort;
using ::std::stack;
using ::std::string;
using ::std::vector;

typedef std::pair<int, int> Coordinates;

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

int main(int argc, char *argv[]) {
  std::fstream my_file;
  vector<vector<int>> energies;
  my_file.open("day11.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    while (!my_file.eof()) {
      string line;
      vector<int> energy_row;
      std::getline(my_file, line);
      for (const char c : line) {
        energy_row.push_back(c - '0');
      }
      energies.push_back(std::move(energy_row));
    }
  }

  long num_flashes = 0;
  for (int i = 0;; i++) {
    for (int j = 0; j < energies.size(); j++) {
      for (int l = 0; l < energies[j].size(); l++) {
        energies[j][l]++;
      }
    }

    bool has_flash = true;
    vector<bool> flashed(100, false);
    while (has_flash) {
      has_flash = false;
      for (int j = 0; j < energies.size(); j++) {
        for (int l = 0; l < energies[j].size(); l++) {
          if (energies[j][l] > 9 && !flashed[10 * j + l]) {
            num_flashes++;
            flashed[10 * j + l] = true;
            has_flash = true;
            if (j > 0) {
              energies[j - 1][l]++;
              if (l > 0) {
                energies[j - 1][l - 1]++;
              }
              if (l < energies[j].size() - 1) {
                energies[j - 1][l + 1]++;
              }
            }
            if (j < energies.size() - 1) {
              energies[j + 1][l]++;
              if (l > 0) {
                energies[j + 1][l - 1]++;
              }
              if (l < energies[j].size() - 1) {
                energies[j + 1][l + 1]++;
              }
            }
            if (l > 0) {
              energies[j][l - 1]++;
            }
            if (l < energies[j].size() - 1) {
              energies[j][l + 1]++;
            }
          }
        }
      }
    }

    bool all_flashed = true;
    for (int i = 0; i < flashed.size(); i++) {
      if (!flashed[i]) {
        all_flashed = false;
      } else {
        energies[i / 10][i % 10] = 0;
      }
    }
    if (all_flashed) {
      cout << "All flashed on step: " << i + 1 << endl;
      return 0;
    }
  }

  my_file.close();
  return 0;
}
