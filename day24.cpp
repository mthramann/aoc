#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <fstream>

using ::std::string;
using ::std::unordered_map;
using ::std::pair;
using ::std::queue;
using ::std::cout;
using ::std::endl;
using ::std::ifstream;
using ::std::to_string;
using ::std::getline;

bool isRegister(string input) {
  return input[0] == 'w' || input[0] == 'x' || input[0] == 'y' ||
         input[0] == 'z';
}

bool IsValid(const string &file, unsigned long long input) {
  ifstream my_file;
  my_file.open("day24.input");
  string input_digits = to_string(input);
  // cout << "Input int " << input << " String " << input_digits << endl;
  for (char c : input_digits) {
    if (c == '0') return false;
  }
  int next_input = 0;
  unordered_map<char, long long> vars;
  vars['x'] = 0;
  vars['y'] = 0;
  vars['z'] = 0;
  vars['w'] = 0;
  string instruction, a, b;
  while (getline(my_file, instruction, ' ')) {
    if (instruction.empty()) continue;
    if (instruction == "inp") {
      getline(my_file, a);
      // cout << instruction << " " << a << " " << input_digits[next_input]
      //      << endl;
      vars[a[0]] = input_digits[next_input++] - '0';
    } else if (instruction == "add") {
      getline(my_file, a, ' ');
      getline(my_file, b);
      // cout << instruction << " " << a << " " << b << endl;
      if (isRegister(b)) {
        vars[a[0]] += vars[b[0]];
      } else {
        vars[a[0]] += std::stoi(b);
      }
    } else if (instruction == "mul") {
      getline(my_file, a, ' ');
      getline(my_file, b);
      // cout << instruction << " " << a << " " << b << endl;
      if (isRegister(b)) {
        vars[a[0]] *= vars[b[0]];
      } else {
        vars[a[0]] *= std::stoi(b);
      }
    } else if (instruction == "div") {
      getline(my_file, a, ' ');
      getline(my_file, b);
      // cout << instruction << " " << a << " " << b << endl;
      if (isRegister(b)) {
        if (vars[b[0]] == 0) return false;
        vars[a[0]] /= vars[b[0]];
      } else {
        if (std::stoi(b) == 0) return false;
        vars[a[0]] /= std::stoi(b);
      }
    } else if (instruction == "mod") {
      getline(my_file, a, ' ');
      getline(my_file, b);
      // cout << instruction << " " << a << " " << b << endl;
      if (vars[a[0]] < 0) return false;
      if (isRegister(b)) {
        if (vars[b[0]] == 0) return false;
        vars[a[0]] %= vars[b[0]];
      } else {
        if (std::stoi(b) == 0) return false;
        vars[a[0]] %= std::stoi(b);
      }
    } else if (instruction == "eql") {
      getline(my_file, a, ' ');
      getline(my_file, b);
      // cout << instruction << " " << a << " " << b << endl;
      if (isRegister(b)) {
        vars[a[0]] = vars[a[0]] == vars[b[0]] ? 1 : 0;
      } else {
        vars[a[0]] = vars[a[0]] == std::stoi(b) ? 1 : 0;
      }
    } else {
      return false;
    }
    // cout << "[" << vars['w'] << ", " << vars['x'] << ", " << vars['y'] << ",
    // "
    //      << vars['z'] << "]" << endl;
  }


  my_file.close();
  return vars['z'] == 0;
}

int main() {
  unsigned long long highest = 99999999999999;
  while (!IsValid("day24.input", highest)) {
    cout << highest << endl;
    highest--;
  }

  cout << highest << endl;
  return 0;
}
