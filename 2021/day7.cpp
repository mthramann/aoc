#include <limits.h>

#include <cmath>
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
  std::vector<int> positions;
  my_file.open(argv[1], std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    std::string data;
    std::getline(my_file, data);
    positions = split(data, ',');
  }

  const int MAX = *std::max_element(positions.begin(), positions.end());
  int min_fuel = INT_MAX;
  int pos = 0;
  for (int i = 0; i < MAX; i++) {
    long fuel = 0;
    for (const int crab : positions) {
      int n = std::abs(i - crab);
      fuel += ((n + 1) * n) / 2;
    }
    if (i == 0) {
      min_fuel = fuel;
    } else if (fuel < min_fuel) {
      min_fuel = fuel;
      pos = i;
    } else if (fuel > min_fuel) {
      break;
    }
  }

  std::cout << "Position: " << pos << " Fuel: " << min_fuel << std::endl;

  my_file.close();
  return 0;
}
