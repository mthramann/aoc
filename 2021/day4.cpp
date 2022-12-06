#include <limits.h>

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const int BOARD_SIZE = 5;

std::vector<int> split(const std::string &s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

class BingoBoard {
 public:
  BingoBoard(std::vector<std::vector<int> > nums) {
    nums_ = nums;
    for (int i = 0; i < BOARD_SIZE; i++) {
      std::vector<bool> row;
      for (int j = 0; j < BOARD_SIZE; j++) {
        row.push_back(false);
      }
      called_.push_back(row);
    }
  }

  bool hasWin() const {
    for (std::vector<bool> row : called_) {
      bool all_true = true;
      for (auto mark : row) {
        if (!mark) {
          all_true = false;
        }
      }
      if (all_true) {
        return true;
      }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
      bool all_true = true;
      for (auto row : called_) {
        if (!row[i]) {
          all_true = false;
        }
      }
      if (all_true) {
        return true;
      }
    }

    return false;
  }

  int unmarkedSum() const {
    int sum = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        if (!called_[i][j]) {
          sum += nums_[i][j];
        }
      }
    }
    return sum;
  }

  // Returns true if this is a win, false otherwise.
  bool markNum(int x) {
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        if (nums_[i][j] == x) {
          called_[i][j] = true;
        }
      }
    }
    return hasWin();
  }

  std::string DebugString() const {
    std::string numbers;
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        int num = nums_[i][j];
        if (called_[i][j]) {
          numbers += "(";
          numbers += std::to_string(num);
          numbers += ")";
        } else {
          numbers += std::to_string(num);
        }
        numbers += ",";
      }
      numbers += "\n";
    }
    return numbers;
  }

 private:
  std::vector<std::vector<int> > nums_;
  std::vector<std::vector<bool> > called_;
};

int main(int argc, char *argv[]) {
  std::fstream my_file;

  my_file.open(argv[1], std::ios::in);
  std::string numbers, line;
  std::vector<BingoBoard> boards;
  if (!my_file) {
    std::cout << "No such file";
  } else {
    std::getline(my_file, numbers);
    std::getline(my_file, line);
    while (!my_file.eof()) {
      std::vector<std::vector<int> > board;
      for (int i = 0; i < BOARD_SIZE; i++) {
        std::vector<int> row;
        for (int j = 0; j < BOARD_SIZE; j++) {
          int temp;
          my_file >> temp;
          row.push_back(temp);
        }
        board.push_back(row);
      }
      std::getline(my_file, line);
      boards.push_back(BingoBoard(board));
    }
  }

  auto nums_to_call = split(numbers, ',');

  for (const auto num : nums_to_call) {
    if (boards.size() == 1) {
      if (boards[0].markNum(num)) {
        std::cout << "Score: " << boards[0].unmarkedSum() * num << std::endl;
        return 0;
      }
    } else {
      std::erase_if(boards,
                    [num](BingoBoard &board) { return board.markNum(num); });
    }
  }

  my_file.close();

  return 0;
}
