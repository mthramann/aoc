#include <limits.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::fstream my_file;

  my_file.open(argv[1], std::ios::in);
  const int BIN_LENGTH = 12;

  std::set<std::string> one_start;
  std::set<std::string> zero_start;
  if (!my_file) {
    std::cout << "No such file";
  } else {
    while (!my_file.eof()) {
      std::string bits;
      my_file >> bits;
      if (bits[0] == '1') {
        one_start.insert(bits);
      } else {
        zero_start.insert(bits);
      }
    }
  }

  std::set<std::string> focus =
      one_start.size() >= zero_start.size() ? one_start : zero_start;

  for (int i = 1; i < BIN_LENGTH; i++) {
    std::set<std::string> ones, zeros;
    for (auto bin : focus) {
      if (bin[i] == '1') {
        ones.insert(bin);
      } else {
        zeros.insert(bin);
      }
    }

    focus = ones.size() >= zeros.size() ? ones : zeros;
    if (focus.size() == 1) {
      break;
    }
  }

  std::string o2 = *focus.begin();

  focus = one_start.size() < zero_start.size() ? one_start : zero_start;
  for (int i = 1; i < BIN_LENGTH; i++) {
    std::set<std::string> ones, zeros;
    for (auto bin : focus) {
      if (bin[i] == '1') {
        ones.insert(bin);
      } else {
        zeros.insert(bin);
      }
    }

    focus = ones.size() < zeros.size() ? ones : zeros;
    if (focus.size() == 1) {
      break;
    }
  }

  std::string co2 = *focus.begin();

  std::cout << o2 << std::endl;
  std::cout << co2 << std::endl;

  int o2_int = std::stoi(o2, nullptr, 2);
  int co2_int = std::stoi(co2, nullptr, 2);
  std::cout << o2_int << std::endl;
  std::cout << co2_int << std::endl;
  std::cout << "Product: " << o2_int * co2_int << std::endl;
  my_file.close();

  return 0;
}
