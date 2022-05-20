#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using ::std::string;

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// Does s contain all the chars of t.
bool contains(const std::string &s, const std::string &t) {
  for (const char c : t) {
    if (s.find(c) == string::npos) {
      return false;
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  std::fstream my_file;

  my_file.open("day8.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    int total = 0;
    while (!my_file.eof()) {
      std::string data;
      std::string target;
      std::getline(my_file, data, '|');
      std::getline(my_file, target);
      std::vector<std::string> signals = split(data, ' ');
      std::vector<std::string> targets = split(target, ' ');
      std::map<std::string, int> signal_to_num;
      std::map<int, std::string> num_to_signal;
      // std::map<char, int> hist;
      for (auto &signal : signals) {
        // for (char c : signal) {
        //   hist[c]++;
        // }
        int length = signal.length();
        std::sort(signal.begin(), signal.end());
        if (length == 2) {
          signal_to_num[signal] = 1;
          num_to_signal[1] = signal;
        } else if (length == 4) {
          signal_to_num[signal] = 4;
          num_to_signal[4] = signal;
        } else if (length == 3) {
          signal_to_num[signal] = 7;
          num_to_signal[7] = signal;
        } else if (length == 7) {
          signal_to_num[signal] = 8;
          num_to_signal[8] = signal;
        }
      }
      for (auto &signal : signals) {
        int length = signal.length();
        if (length == 5) {
          std::string &one = num_to_signal[1];
          if (contains(signal, one)) {
            signal_to_num[signal] = 3;
            num_to_signal[3] = signal;
            continue;
          }
          bool is_two = false;
          for (auto digit : num_to_signal[4]) {
            if (num_to_signal[1].find(digit) == string::npos &&
                signal.find(digit) == string::npos) {
              signal_to_num[signal] = 2;
              num_to_signal[2] = signal;
              is_two = true;
              continue;
            }
          }
          if (!is_two) {
            signal_to_num[signal] = 5;
            num_to_signal[5] = signal;
          }
        } else if (length == 6) {
          if (!contains(signal, num_to_signal[1])) {
            signal_to_num[signal] = 6;
            num_to_signal[6] = signal;
            continue;
          }
          if (!contains(signal, num_to_signal[4])) {
            signal_to_num[signal] = 0;
            num_to_signal[0] = signal;
            continue;
          }
          signal_to_num[signal] = 9;
          num_to_signal[9] = signal;
        }
      }

      int num = 0;
      for (int i = 0; i < targets.size(); i++) {
        // 	      int hist_total = 0;
        // for (char c : targets[i]) {
        //   hist_total += hist[c];
        // }
        // std::cout << "Hist total: " << hist_total << std::endl;
        std::sort(targets[i].begin(), targets[i].end());
        num = num * 10 + signal_to_num[targets[i]];
      }
      total += num;
    }
    std::cout << "Total: " << total << std::endl;
  }

  my_file.close();
  return 0;
}
