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

std::vector<int> split(const std::string& s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

bool infImage(const vector<vector<bool>>& image, const bool infinite, int x,
              int y) {
  if (y >= 0 && y < image.size() && x >= 0 && x < image[y].size()) {
    return image[y][x];
  }
  return infinite;
}

int getNum(const vector<vector<bool>>& image, const bool infinite, int x,
           int y) {
  int ret = 0;
  ret |= (infImage(image, infinite, x - 1, y - 1) << 8);
  ret |= (infImage(image, infinite, x, y - 1) << 7);
  ret |= (infImage(image, infinite, x + 1, y - 1) << 6);
  ret |= (infImage(image, infinite, x - 1, y) << 5);
  ret |= (infImage(image, infinite, x, y) << 4);
  ret |= (infImage(image, infinite, x + 1, y) << 3);
  ret |= (infImage(image, infinite, x - 1, y + 1) << 2);
  ret |= (infImage(image, infinite, x, y + 1) << 1);
  ret |= infImage(image, infinite, x + 1, y + 1);
  return ret;
}

int main(int argc, char* argv[]) {
  std::fstream my_file;
  string conversion_key;
  vector<vector<bool>> input;
  my_file.open("day20.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    getline(my_file, conversion_key);
    string line;
    while (!my_file.eof()) {
      getline(my_file, line);
      if (line.empty()) continue;
      vector<bool> row;
      for (const auto c : line) {
        if (c == '#') row.push_back(true);
        if (c == '.') row.push_back(false);
      }
      input.push_back(std::move(row));
    }
  }

  bool infinite = false;
  for (int i = 0; i < 50; i++) {
    vector<vector<bool>> new_image;
    int input_rows = input.size();
    for (int j = -1; j < input_rows + 1; j++) {
      vector<bool> new_row;
      int row_length = input[0].size();
      for (int k = -1; k < row_length + 1; k++) {
        new_row.push_back(conversion_key[getNum(input, infinite, k, j)] == '#');
      }
      new_image.push_back(new_row);
    }
    infinite = infinite ? conversion_key[511] == '#' : conversion_key[0] == '#';
    input = new_image;
  }

  int lit = 0;
  for (auto row : input) {
    for (bool b : row) {
      if (b) {
        lit++;
        cout << '#';
      } else {
        cout << '.';
      }
    }
    cout << endl;
  }
  //  cout << "Lit: " << lit << endl;

  my_file.close();
  return 0;
}
