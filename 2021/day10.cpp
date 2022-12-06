#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::set;
using ::std::sort;
using ::std::stack;
using ::std::string;
using ::std::vector;

typedef std::pair<int, int> Coordinates;

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

int main(int argc, char *argv[]) {
  std::fstream my_file;

  my_file.open("day10.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    vector<long> scores;
    while (!my_file.eof()) {
      bool is_corrupt = false;
      stack<char> chunks;
      string line;
      std::getline(my_file, line);
      for (const char c : line) {
        if (c == '(' || c == '{' || c == '[' || c == '<') {
          chunks.push(c);
          continue;
        }
        if (c == ')') {
          if (chunks.empty() || chunks.top() != '(') {
            is_corrupt = true;
            break;
          } else {
            chunks.pop();
          }
        } else if (c == '}') {
          if (chunks.empty() || chunks.top() != '{') {
            is_corrupt = true;
            break;
          } else {
            chunks.pop();
          }
        } else if (c == ']') {
          if (chunks.empty() || chunks.top() != '[') {
            is_corrupt = true;
            break;
          } else {
            chunks.pop();
          }
        } else if (c == '>') {
          if (chunks.empty() || chunks.top() != '<') {
            is_corrupt = true;
            break;
          } else {
            chunks.pop();
          }
        }
      }
      long incomplete_score = 0;
      while (!is_corrupt && !chunks.empty()) {
        char c = chunks.top();
        chunks.pop();
        incomplete_score *= 5;
        if (c == '(') {
          incomplete_score += 1;
        } else if (c == '{') {
          incomplete_score += 3;
        } else if (c == '[') {
          incomplete_score += 2;
        } else if (c == '<') {
          incomplete_score += 4;
        }
      }
      if (incomplete_score != 0) {
        cout << incomplete_score << endl;
        scores.push_back(incomplete_score);
      }
    }
    sort(scores.begin(), scores.end());
    if (!scores.empty()) {
      cout << "Incomplete score: " << scores[scores.size() / 2] << endl;
    }
  }

  my_file.close();
  return 0;
}
