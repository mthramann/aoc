#include <limits.h>

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

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
  std::map<int, std::map<int, int> > coords;
  my_file.open(argv[1], std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    while (!my_file.eof()) {
      std::string temp;
      int x0, y0, x1, y1;
      std::getline(my_file, temp, ',');
      x0 = std::stoi(temp);
      std::getline(my_file, temp, ' ');
      y0 = std::stoi(temp);
      std::getline(my_file, temp, ' ');
      std::getline(my_file, temp, ',');
      x1 = std::stoi(temp);
      std::getline(my_file, temp);
      y1 = std::stoi(temp);

      if (x0 == x1) {
        int inc = y1 < y0 ? -1 : 1;
        for (int i = y0; i != y1; i += inc) {
          coords[x0][i]++;
        }
        coords[x0][y1]++;
      } else if (y0 == y1) {
        int inc = x1 < x0 ? -1 : 1;
        for (int i = x0; i != x1; i += inc) {
          coords[i][y0]++;
        }
        coords[x1][y0]++;
      } else {
        int x_inc = x1 < x0 ? -1 : 1;
        int y_inc = y1 < y0 ? -1 : 1;
        while (
            x0 !=
            x1) {  // This should be sufficient if we're guaranteed 45 degrees
          coords[x0][y0]++;
          x0 += x_inc;
          y0 += y_inc;
        }
        coords[x1][y1]++;
      }
      //      std::cout << x0 << "," << y0 << " -> " << x1 << "," << y1 << "\n";
    }
  }

  int overlaps = 0;
  for (const auto [x, col] : coords) {
    for (const auto [y, freq] : col) {
      if (freq > 1) {
        overlaps++;
      }
    }
  }

  std::cout << "Overlaps: " << overlaps << std::endl;

  my_file.close();
  return 0;
}
