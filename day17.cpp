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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::getline;
using ::std::optional;
using ::std::pair;
using ::std::priority_queue;
using ::std::set;
using ::std::sort;
using ::std::stack;
using ::std::string;
using ::std::unique_ptr;
using ::std::unordered_map;
using ::std::unordered_set;
using ::std::vector;

vector<pair<int, int>> triangle_nums = {
    {0, 0},   {1, 1},   {3, 2},    {6, 3},   {10, 4},  {15, 5},
    {21, 6},  {28, 7},  {36, 8},   {45, 9},  {55, 10}, {66, 11},
    {78, 12}, {91, 13}, {105, 14}, {120, 15}};

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
  int x_start, x_end;
  int y_start, y_end;
  string num;
  my_file.open("day17.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    string line;
    getline(my_file, line, '=');
    getline(my_file, num, '.');
    x_start = std::stoi(num);
    getline(my_file, line, '.');
    getline(my_file, num, ',');
    x_end = std::stoi(num);
    getline(my_file, line, '=');
    getline(my_file, num, '.');
    y_start = std::stoi(num);
    getline(my_file, line, '.');
    getline(my_file, num);
    y_end = std::stoi(num);
    cout << "target area: x=" << x_start << ".." << x_end << ", y=" << y_start
         << ".." << y_end << endl;
  }

  int overall_highest = 0;
  set<pair<int, int>> velocities;
  for (int x = 0; x < 117; x++) {
    for (int y = -5000; y < 5000; y++) {
      int xv = x, yv = y;
      int xpos = 0, ypos = 0;
      bool hit = false;
      while (ypos >= y_start) {
        if (x_start <= xpos && xpos <= x_end && y_start <= ypos &&
            ypos <= y_end) {
          hit = true;
        }
        xpos += xv;
        if (xv > 0) xv--;
        if (xv < 0) xv++;
        ypos += yv;
        yv--;
      }
      if (hit) {
        cout << "(" << x << ", " << y << ")" << endl;
        velocities.insert({x, y});
      }
    }
  }

  cout << "Num: " << velocities.size() << endl;

  my_file.close();
  return 0;
}
