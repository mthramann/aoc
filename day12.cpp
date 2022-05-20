#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::getline;
using ::std::set;
using ::std::sort;
using ::std::stack;
using ::std::string;
using ::std::unordered_map;
using ::std::vector;

int NumPaths(const unordered_map<string, vector<string>> &caves,
             const string &start, unordered_map<string, int> visited,
             bool doubled) {
  if (start == "end") {
    return 1;
  }
  int paths = 0;
  for (const string &next : caves.at(start)) {
    if (next == "end") {
      paths += 1;
      continue;
    }
    if (next[0] > 96) {  // Is lowercase
      if (visited[next] == 0) {
        visited[next]++;
        paths += NumPaths(caves, next, visited, doubled);
        visited[next]--;
      } else if (visited[next] == 1 && !doubled) {
        visited[next]++;
        paths += NumPaths(caves, next, visited, true);
        visited[next]--;
      }
    } else {
      paths += NumPaths(caves, next, visited, doubled);
    }
  }
  return paths;
}

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
  unordered_map<string, vector<string>> caves;
  std::fstream my_file;
  my_file.open("day12.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    string source, dest;
    while (!my_file.eof()) {
      getline(my_file, source, '-');
      getline(my_file, dest);
      if (source == "start" || dest == "end") {
        caves[source].push_back(dest);
      } else if (dest == "start" || source == "end") {
        caves[dest].push_back(source);
      } else {
        caves[source].push_back(dest);
        caves[dest].push_back(source);
      }
    }
  }

  unordered_map<string, int> visited;
  visited.reserve(caves.size());
  cout << "Num paths: " << NumPaths(caves, "start", visited, false) << endl;

  my_file.close();
  return 0;
}
