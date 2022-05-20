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
  const int NUM_DAYS = 256;
  my_file.open(argv[1], std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    std::string data;
    std::map<int, long> times;
    for (int i = 0; i < 9; i++) {
      times[i] = 0;
    }
    std::getline(my_file, data);
    std::vector<int> input = split(data, ',');

    for (const auto age : input) {
      times[age]++;
    }

    for (int i = 0; i < NUM_DAYS; i++) {
      std::map<int, long> new_times;
      for (int i = 0; i < 9; i++) {
        new_times[i] = 0;
      }
      for (const auto [age, count] : times) {
        if (age == 0) {
          new_times[6] += count;
          new_times[8] += count;
        } else {
          new_times[age - 1] += count;
        }
      }
      times = new_times;
    }

    long total_fish = 0;
    for (const auto [age, num] : times) {
      total_fish += num;
    }

    std::cout << "Num fish: " << total_fish << std::endl;
  }

  my_file.close();
  return 0;
}
