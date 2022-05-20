#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::getline;
using ::std::ifstream;
using ::std::pair;
using ::std::queue;
using ::std::string;
using ::std::unordered_map;
using ::std::vector;

bool moveEast(vector<string> &rows) {
  bool move = false;
  for (string &row : rows) {
    bool zero_occupied = row[0] != '.';
    for (int i = 0; i < row.size(); i++) {
      if (i == row.size() - 1 && zero_occupied) continue;
      if (row[i] == '>' && row[(i + 1) % row.size()] == '.') {
        move = true;
        row[i] = '.';
        row[(i + 1) % row.size()] = '>';
        i++;
      }
    }
  }
  return move;
}

bool moveSouth(vector<string> &rows) {
  bool move = false;
  for (int i = 0; i < rows[0].size(); i++) {
    bool zero_occupied = rows[0][i] != '.';
    for (int j = 0; j < rows.size(); j++) {
      if (j == rows.size() - 1 && zero_occupied) continue;
      if (rows[j][i] == 'v' && rows[(j + 1) % rows.size()][i] == '.') {
        move = true;
        rows[j][i] = '.';
        rows[(j + 1) % rows.size()][i] = 'v';
        j++;
      }
    }
  }
  return move;
}

bool cucMove(vector<string> &rows) {
  bool east = moveEast(rows);
  bool south = moveSouth(rows);
  return east || south;
}

int main() {
  ifstream my_file;
  vector<string> rows;
  my_file.open("day25.input");
  while (!my_file.eof()) {
    string row;
    getline(my_file, row);
    if (row.empty()) continue;
    rows.push_back(std::move(row));
  }
  my_file.close();

  // for (int i = 0; i < 4; i++) {
  //   cucMove(rows);
  //   for (auto row : rows) {
  //     cout << row << endl;
  //   }
  //   cout << endl;
  // }

  int i = 0;
  while (cucMove(rows)) {
    i++;
    // cout << i << endl;
    // for (auto row : rows) {
    //   cout << row << endl;
    // }
    // cout << endl;
  }

  cout << i + 1 << endl;
  return 0;
}
