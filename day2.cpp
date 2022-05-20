#include <limits.h>

#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::fstream my_file;
  int x = 0;
  int y = 0;
  int aim = 0;
  my_file.open(argv[1], std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    while (!my_file.eof()) {
      std::string direction;
      int distance;
      my_file >> direction >> distance;
      if (direction == "forward") {
        x += distance;
        y += aim * distance;
      } else if (direction == "up") {
        aim -= distance;
      } else if (direction == "down") {
        aim += distance;
      }
    }
  }

  std::cout << "X: " << x << " Y: " << y << std::endl;
  std::cout << "Product: " << x * y << std::endl;
  my_file.close();

  return 0;
}
