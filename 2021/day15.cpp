#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
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
using ::std::priority_queue;
using ::std::set;
using ::std::sort;
using ::std::stack;
using ::std::string;
using ::std::unordered_map;
using ::std::unordered_set;
using ::std::vector;

typedef pair<int, int> Coord;
typedef pair<Coord, int> Dist;

auto comp_dist = [](const Dist a, const Dist b) { return a.second > b.second; };

int inc(int base, int offset) {
  int ret = base + offset;
  return ret > 9 ? ret - 9 : ret;
}

std::vector<int> split(const std::string &s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

int dijkstra(const vector<vector<int>> &grid) {
  priority_queue<Dist, vector<Dist>, decltype(comp_dist)> queue(comp_dist);
  vector<vector<int>> min_paths(grid.size(),
                                vector<int>(grid[0].size(), INT_MAX));
  min_paths[0][0] = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      queue.emplace(std::pair(j, i), min_paths[i][j]);
    }
  }

  while (!queue.empty()) {
    auto [coords, distance] = queue.top();
    queue.pop();
    int x = coords.first, y = coords.second;
    if (distance != min_paths[y][x]) continue;
    if (x > 0) {
      int left = grid[y][x - 1] + min_paths[y][x];
      if (left < min_paths[y][x - 1]) {
        min_paths[y][x - 1] = left;
        queue.emplace(std::pair(x - 1, y), left);
      }
    }
    if (y > 0) {
      int up = grid[y - 1][x] + min_paths[y][x];
      if (up < min_paths[y - 1][x]) {
        min_paths[y - 1][x] = up;
        queue.emplace(std::pair(x, y - 1), up);
      }
    }
    if (x < grid[y].size() - 1) {
      int right = grid[y][x + 1] + min_paths[y][x];
      if (right < min_paths[y][x + 1]) {
        min_paths[y][x + 1] = right;
        queue.emplace(std::pair(x + 1, y), right);
      }
    }
    if (y < grid.size() - 1) {
      int down = grid[y + 1][x] + min_paths[y][x];
      if (down < min_paths[y + 1][x]) {
        min_paths[y + 1][x] = down;
        queue.emplace(std::pair(x, y + 1), down);
      }
    }
  }
  return min_paths[grid.size() - 1][grid[0].size() - 1];
}

int main(int argc, char *argv[]) {
  std::fstream my_file;
  vector<vector<int>> grid;
  my_file.open("day15.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    while (!my_file.eof()) {
      string line;
      getline(my_file, line);
      if (line.empty()) continue;
      vector<int> row;
      for (char c : line) {
        row.push_back(c - '0');
      }
      grid.push_back(std::move(row));
    }
  }

  vector<vector<int>> big_grid(grid);
  for (int i = 1; i < 5; i++) {
    for (int j = 0; j < grid.size(); j++) {
      for (int k = 0; k < grid[j].size(); k++) {
        big_grid[j].push_back(inc(grid[j][k], i));
      }
    }
  }

  for (int i = 1; i < 5; i++) {
    for (int j = 0; j < grid.size(); j++) {
      vector<int> new_row;
      for (int k = 0; k < big_grid[j].size(); k++) {
        new_row.push_back(inc(big_grid[j][k], i));
      }
      big_grid.push_back(std::move(new_row));
    }
  }

  // for (int i = 0; i < big_grid.size(); i++) {
  //   for (int j = 0; j < big_grid[i].size(); j++) {
  //     cout << big_grid[i][j];
  //   }
  //   cout << endl;
  // }

  cout << "Min " << dijkstra(big_grid) << endl;

  my_file.close();
  return 0;
}
