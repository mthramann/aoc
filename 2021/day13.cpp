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

typedef pair<int, int> Coord;
typedef pair<bool, int> Fold;

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
  set<Coord> coordinates;
  vector<Fold> folds;

  my_file.open("day13.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    string line;
    while (!my_file.eof()) {
      getline(my_file, line);
      if (line.empty()) continue;
      if (line.find("fold") == string::npos) {
        auto coords = split(line, ',');
        coordinates.emplace(coords[0], coords[1]);
      } else {
        bool axis = line[11] == 'x';
        int position = std::stoi(line.substr(13));
        folds.emplace_back(axis, position);
      }
    }
  }

  for (Fold first_fold : folds) {
    set<Coord> new_coordinates;
    for (Coord coord : coordinates) {
      int new_x = coord.first;
      int new_y = coord.second;
      if (first_fold.first) {
        if (coord.first > first_fold.second) {
          int diff = coord.first - first_fold.second;
          new_x = first_fold.second - diff;
        }
      } else {
        if (coord.second > first_fold.second) {
          int diff = coord.second - first_fold.second;
          new_y = first_fold.second - diff;
        }
      }
      new_coordinates.emplace(new_x, new_y);
    }
    coordinates = new_coordinates;
  }

  int max_x = 0, max_y = 0;
  for (Coord coord : coordinates) {
    if (coord.first > max_x) max_x = coord.first;
    if (coord.second > max_y) max_y = coord.second;
  }

  vector<vector<char>> image(max_y + 1, vector<char>(max_x + 1, ' '));
  for (Coord coord : coordinates) {
    image[coord.second][coord.first] = '';
  }

  for (auto line : image) {
    for (char character : line) {
      cout << character;
    }
    cout << endl;
  }
  my_file.close();
  return 0;
}
