#include <limits.h>
#include <stdio.h>
#include <string.h>

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
using ::std::max;
using ::std::min;
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

struct Cube {
  Cube() {}
  Cube(int xl, int xh, int yl, int yh, int zl, int zh)
      : x_start(xl),
        x_end(xh),
        y_start(yl),
        y_end(yh),
        z_start(zl),
        z_end(zh) {}

  int x_start;
  int x_end;
  int y_start;
  int y_end;
  int z_start;
  int z_end;

  unsigned long long vol() {
    unsigned long long out = 1 + x_end - x_start;
    out *= 1 + y_end - y_start;
    out *= 1 + z_end - z_start;
    return out;
  }
};

struct Step {
  bool on;
  Cube cube;
};

bool intersects(const Cube& c1, const Cube& c2) {
  return !(c1.x_start > c2.x_end || c1.x_end < c2.x_start ||
           c1.y_start > c2.y_end || c1.y_end < c2.y_start ||
           c1.z_start > c2.z_end || c1.z_end < c2.z_start);
}

void splitCube(const Cube& c1, const Cube& c2, vector<Cube>& to_add) {
  Cube c(max(c1.x_start, c2.x_start), min(c1.x_end, c2.x_end),
         max(c1.y_start, c2.y_start), min(c1.y_end, c2.y_end),
         max(c1.z_start, c2.z_start), min(c1.z_end, c2.z_end));
  if (c1.z_start < c.z_start)
    to_add.emplace_back(c1.x_start, c1.x_end, c1.y_start, c1.y_end, c1.z_start,
                        c.z_start - 1);  // bottom part
  if (c.z_end < c1.z_end)
    to_add.emplace_back(c1.x_start, c1.x_end, c1.y_start, c1.y_end, c.z_end + 1,
                        c1.z_end);  // top part
  if (c1.x_start < c.x_start)
    to_add.emplace_back(c1.x_start, c.x_start - 1, c1.y_start, c1.y_end,
                        c.z_start, c.z_end);  // middle portions
  if (c.x_end < c1.x_end)
    to_add.emplace_back(c.x_end + 1, c1.x_end, c1.y_start, c1.y_end, c.z_start,
                        c.z_end);
  if (c1.y_start < c.y_start)
    to_add.emplace_back(c.x_start, c.x_end, c1.y_start, c.y_start - 1,
                        c.z_start, c.z_end);
  if (c.y_end < c1.y_end)
    to_add.emplace_back(c.x_start, c.x_end, c.y_end + 1, c1.y_end, c.z_start,
                        c.z_end);
}

std::vector<int> split(const std::string& s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

int main(int argc, char* argv[]) {
  std::fstream my_file;
  vector<Cube> cubes;
  vector<Step> steps;
  my_file.open("day22.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    string line;
    string setting;
    while (!my_file.eof()) {
      getline(my_file, line);
      if (line.empty()) continue;
      Step step;
      step.on = (line[1] == 'n');
      char temp[16];
      std::sscanf(line.c_str(), "%s x=%d..%d,y=%d..%d,z=%d..%d", temp,
                  &step.cube.x_start, &step.cube.x_end, &step.cube.y_start,
                  &step.cube.y_end, &step.cube.z_start, &step.cube.z_end);
      steps.push_back(std::move(step));
    }
  }

  for (const auto step : steps) {
    vector<Cube> to_add;
    for (auto cube : cubes) {
      if (intersects(cube, step.cube)) {
        splitCube(cube, step.cube, to_add);
      } else {
        to_add.push_back(cube);
      }
    }
    if (step.on) to_add.push_back(step.cube);
    cubes = std::move(to_add);
  }

  unsigned long long on = 0;
  for (Cube cube : cubes) {
    on += cube.vol();
  }

  cout << on << endl;

  my_file.close();
  return 0;
}
