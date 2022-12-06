#include <limits.h>

#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::fstream my_file;
  std::vector<int> depths;
  my_file.open(argv[1], std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    while (!my_file.eof()) {
      int depth;
      my_file >> depth;
      depths.push_back(depth);
    }
  }
  my_file.close();

  int increases = 0;
  for (int i = 0; i < depths.size() - 3; i++) {
    std::cout << "First: " << depths[i] << " Last: " << depths[i + 3]
              << std::endl;
    if (depths[i] < depths[i + 3]) {
      std::cout << "Increase!" << std::endl;
      increases++;
    }
  }

  std::cout << "Increases: " << increases << std::endl;

  return 0;
}
