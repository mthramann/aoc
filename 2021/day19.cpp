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

struct Coord {
  Coord(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}

  int x;
  int y;
  int z;

  bool operator==(const Coord& t) const {
    return this->x == t.x && this->y == t.y && this->z == t.z;
  }
};

class MyHashFunction {
 public:
  size_t operator()(const Coord& t) const {
    return (t.x * 2 + t.y * 3 + t.z * 7);
  }
};

bool operator<(const Coord& lhs, const Coord& rhs) {
  if (lhs.x == rhs.x) {
    if (lhs.y == rhs.y) {
      return lhs.z < rhs.z;
    }
    return lhs.y < rhs.y;
  }
  return lhs.x < rhs.x;
}

typedef unordered_set<Coord, MyHashFunction> ScannerView;

std::vector<int> split(const std::string& s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

Coord getDeltas(ScannerView beacons, Coord point, int rx, int ry, int rz,
                int sx, int sy, int sz, ScannerView& deltas) {
  vector<int> point_v = {point.x, point.y, point.z};

  for (Coord beacon : beacons) {
    vector<int> beacon_v = {beacon.x, beacon.y, beacon.z};
    deltas.insert({sx * (beacon_v[rx] - point_v[rx]),
                   sy * (beacon_v[ry] - point_v[ry]),
                   sz * (beacon_v[rz] - point_v[rz])});
  }

  return {-sx * point_v[rx], -sy * point_v[ry], -sz * point_v[rz]};
}

bool merges(ScannerView& overall, ScannerView candidate,
            vector<Coord>& found_scanners) {
  if (overall.empty()) {
    overall = std::move(candidate);
    found_scanners.push_back({0, 0, 0});
    return true;
  }

  //  [facing, up, right, sign_f, sign_u, sign_r]
  vector<tuple<int, int, int, int, int, int>> axis = {
      {0, 1, 2, 1, 1, 1},     //  x  y  z
      {0, 1, 2, 1, -1, -1},   //  x -y -z
      {0, 2, 1, 1, 1, -1},    //  x  z -y
      {0, 2, 1, 1, -1, 1},    //  x -z  y
      {0, 1, 2, -1, 1, -1},   // -x  y -z
      {0, 1, 2, -1, -1, 1},   // -x -y  z
      {0, 2, 1, -1, 1, 1},    // -x  z  y
      {0, 2, 1, -1, -1, -1},  // -x -z -y
  };

  vector<tuple<int, int, int, int, int, int>> rot;
  for (int a = 0; a < 3; a++)
    for (const auto& [dx, dy, dz, sx, sy, sz] : axis)
      rot.push_back({(a + dx) % 3, (a + dy) % 3, (a + dz) % 3, sx, sy, sz});

  for (const auto& c_beacon : candidate) {
    for (const auto& [rx, ry, rz, sx, sy, sz] : rot) {
      ScannerView deltas;
      Coord scanner =
          getDeltas(candidate, c_beacon, rx, ry, rz, sx, sy, sz, deltas);
      for (const auto& beacon : overall) {
        int matches = 0;
        for (auto delta : deltas) {
          matches += overall.count(
              {delta.x + beacon.x, delta.y + beacon.y, delta.z + beacon.z});
        }
        if (matches >= 12) {
          for (auto delta : deltas) {
            overall.insert(
                {delta.x + beacon.x, delta.y + beacon.y, delta.z + beacon.z});
          }
          found_scanners.push_back({scanner.x + beacon.x, scanner.y + beacon.y,
                                    scanner.z + beacon.z});
          return true;
        }
      }
    }
  }

  return false;
}

int main(int argc, char* argv[]) {
  std::fstream my_file;
  queue<ScannerView> scanners;
  my_file.open("day19.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    string line;
    ScannerView scanner;
    while (!my_file.eof()) {
      getline(my_file, line);
      if (line.size() < 2) {
        scanners.push(scanner);
        scanner.clear();
      } else if (line[1] != '-') {
        int x, y, z;
        std::sscanf(line.c_str(), "%d,%d,%d\n", &x, &y, &z);
        scanner.insert({x, y, z});
      }
    }
  }

  vector<Coord> found_scanners;
  ScannerView overall;
  while (!scanners.empty()) {
    ScannerView scanner = scanners.front();
    scanners.pop();
    if (!merges(overall, scanner, found_scanners)) {
      scanners.push(scanner);
    }
  }

  cout << overall.size() << endl;
  int manhattan_max = 0;
  for (int i = 0; i < found_scanners.size(); i++) {
    for (int j = i + 1; j < found_scanners.size(); j++) {
      manhattan_max =
          std::max(manhattan_max,
                   std::abs(found_scanners[i].x - found_scanners[j].x) +
                       std::abs(found_scanners[i].y - found_scanners[j].y) +
                       std::abs(found_scanners[i].z - found_scanners[j].z));
    }
  }

  cout << manhattan_max << endl;

  my_file.close();
  return 0;
}
