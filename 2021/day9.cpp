#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::set;
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

// Given coordinates for a low point, find the size of its basin.
int basinSize(vector<vector<int>> depths, int x, int y) {
  set<Coordinates> in_basin;
  set<Coordinates> candidates;
  candidates.insert(Coordinates(x, y));
  while (!candidates.empty()) {
    Coordinates a = *candidates.begin();
    candidates.erase(candidates.begin());
    if (depths[a.first][a.second] == 9) {
      continue;
    }
    in_basin.insert(a);
    if (a.first != 0) {
      Coordinates above(a.first - 1, a.second);
      if (!in_basin.contains(above)) {
        candidates.insert(above);
      }
    }
    if (a.second != 0) {
      Coordinates before(a.first, a.second - 1);
      if (!in_basin.contains(before)) {
        candidates.insert(before);
      }
    }
    if (a.first != depths.size() - 1) {
      Coordinates below(a.first + 1, a.second);
      if (!in_basin.contains(below)) {
        candidates.insert(below);
      }
    }
    if (a.second != depths[a.first].size() - 1) {
      Coordinates after(a.first, a.second + 1);
      if (!in_basin.contains(after)) {
        candidates.insert(after);
      }
    }
  }
  return in_basin.size();
}

int main(int argc, char *argv[]) {
  std::fstream my_file;

  my_file.open("day9.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    vector<vector<int>> depths;
    while (!my_file.eof()) {
      vector<int> row;
      string line;
      std::getline(my_file, line);
      for (const char c : line) {
        row.push_back(c - 48);
      }
      depths.push_back(std::move(row));
    }
    vector<int> basin_sizes;
    for (int i = 0; i < depths.size(); i++) {
      for (int j = 0; j < depths[i].size(); j++) {
        const int depth = depths[i][j];
        if ((i == 0 || depths[i - 1][j] > depth) &&
            (j == 0 || depths[i][j - 1] > depth) &&
            (i == depths.size() - 1 || depths[i + 1][j] > depth) &&
            (j == depths[i].size() - 1 || depths[i][j + 1] > depth)) {
          basin_sizes.push_back(basinSize(depths, i, j));
        }
      }
    }

    std::sort(basin_sizes.begin(), basin_sizes.end());
    int product = 1;
    for (int i = 0; i < 3; i++) {
      product *= basin_sizes[basin_sizes.size() - (i + 1)];
    }

    cout << "Product: " << product << endl;
  }

  my_file.close();
  return 0;
}
