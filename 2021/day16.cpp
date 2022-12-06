#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using ::std::cout;
using ::std::endl;
using ::std::getline;
using ::std::optional;
using ::std::pair;
using ::std::priority_queue;
using ::std::set;
using ::std::sort;
using ::std::stack;
using ::std::string;
using ::std::unique_ptr;
using ::std::unordered_map;
using ::std::unordered_set;
using ::std::vector;

std::vector<int> split(const std::string &s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

vector<bool> HexToBits(const string &str) {
  vector<bool> ret;
  for (const char c : str) {
    switch (c) {
      case '0':
        ret.push_back(0);
        ret.push_back(0);
        ret.push_back(0);
        ret.push_back(0);
        break;
      case '1':
        ret.push_back(0);
        ret.push_back(0);
        ret.push_back(0);
        ret.push_back(1);
        break;
      case '2':
        ret.push_back(0);
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(0);
        break;
      case '3':
        ret.push_back(0);
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(1);
        break;
      case '4':
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(0);
        ret.push_back(0);
        break;
      case '5':
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(0);
        ret.push_back(1);
        break;
      case '6':
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(1);
        ret.push_back(0);
        break;
      case '7':
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(1);
        ret.push_back(1);
        break;
      case '8':
        ret.push_back(1);
        ret.push_back(0);
        ret.push_back(0);
        ret.push_back(0);
        break;
      case '9':
        ret.push_back(1);
        ret.push_back(0);
        ret.push_back(0);
        ret.push_back(1);
        break;
      case 'A':
        ret.push_back(1);
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(0);
        break;
      case 'B':
        ret.push_back(1);
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(1);
        break;
      case 'C':
        ret.push_back(1);
        ret.push_back(1);
        ret.push_back(0);
        ret.push_back(0);
        break;
      case 'D':
        ret.push_back(1);
        ret.push_back(1);
        ret.push_back(0);
        ret.push_back(1);
        break;
      case 'E':
        ret.push_back(1);
        ret.push_back(1);
        ret.push_back(1);
        ret.push_back(0);
        break;
      case 'F':
        ret.push_back(1);
        ret.push_back(1);
        ret.push_back(1);
        ret.push_back(1);
        break;
    }
  }
  return ret;
}

unsigned long getNumForRange(vector<bool> bits, int start, int end) {
  unsigned long num = 0;
  for (int i = start; i < end; i++) {
    num *= 2;
    if (bits[i]) {
      num += 1;
    }
  }
  return num;
}

class Packet {
 public:
  Packet(vector<bool> bits, int &ind) {
    version_ = getNumForRange(bits, ind, ind + 3);
    ind += 3;
    type_id_ = getNumForRange(bits, ind, ind + 3);
    ind += 3;
    if (type_id_ == 4) {
      vector<bool> num;
      while (bits[ind]) {
        for (int i = 1; i < 5; i++) {
          num.push_back(bits[ind + i]);
        }
        ind += 5;
      }
      for (int i = 1; i < 5; i++) {
        num.push_back(bits[ind + i]);
      }
      ind += 5;
      literal_ = getNumForRange(num, 0, num.size());
    } else {
      if (bits[ind]) {
        ind++;
        int num_subpackets = getNumForRange(bits, ind, ind + 11);
        ind += 11;
        for (int i = 0; i < num_subpackets; i++) {
          sub_packets_.emplace_back(new Packet(bits, ind));
        }
      } else {
        ind++;
        int end = ind + getNumForRange(bits, ind, ind + 15) + 15;
        ind += 15;
        while (ind < end) {
          sub_packets_.emplace_back(new Packet(bits, ind));
        }
      }
    }
  }

  unsigned long evaluate() {
    switch (type_id_) {
      case 0: {
        cout << "(+ ";
        unsigned long sum = 0;
        for (unique_ptr<Packet> &packet : sub_packets_) {
          sum += packet->evaluate();
        }
        cout << ") ";
        return sum;
      }
      case 1: {
        cout << "(* ";
        unsigned long product = 1;
        for (unique_ptr<Packet> &packet : sub_packets_) {
          product *= packet->evaluate();
        }
        cout << ") ";
        return product;
      }
      case 2: {
        cout << "(min ";
        unsigned long min = sub_packets_[0]->evaluate();
        for (unique_ptr<Packet> &packet : sub_packets_) {
          unsigned long val = packet->evaluate();
          if (val < min) {
            min = val;
          }
        }
        cout << ") ";
        return min;
      }
      case 3: {
        cout << "(max ";
        unsigned long max = 0;
        for (unique_ptr<Packet> &packet : sub_packets_) {
          unsigned long val = packet->evaluate();
          if (val > max) {
            max = val;
          }
        }
        cout << ") ";
        return max;
      }
      case 4: {
        cout << literal_.value() << " ";
        return literal_.value();
      }
      case 5: {
        cout << "(> ";
        bool temp = sub_packets_[0]->evaluate() > sub_packets_[1]->evaluate();
        cout << ") ";
        return temp;
      }
      case 6: {
        cout << "(< ";
        bool temp = sub_packets_[0]->evaluate() < sub_packets_[1]->evaluate();
        cout << ") ";
        return temp;
      }
      case 7: {
        cout << "(= ";
        bool temp = sub_packets_[0]->evaluate() == sub_packets_[1]->evaluate();
        cout << ") ";
        return temp;
      }
    }
    return 0;
  }

  int version_sum() {
    int sum = 0;
    sum += version_;
    for (unique_ptr<Packet> &packet : sub_packets_) {
      int temp = packet->version_sum();
      sum += temp;
    }
    return sum;
  }
  int version_;
  int type_id_;
  optional<unsigned long> literal_;
  vector<unique_ptr<Packet>> sub_packets_;
};

int main(int argc, char *argv[]) {
  std::fstream my_file;
  vector<bool> bits;
  int version_sum = 0;
  my_file.open("day16.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    string line;
    getline(my_file, line);
    bits = HexToBits(line);
  }

  // for (auto bit : bits) {
  //   cout << (bit ? 1 : 0);
  // }
  // cout << endl;

  int ind = 0;
  Packet top_level(bits, ind);
  unsigned long res = top_level.evaluate();
  cout << endl << "Equals: " << res << endl;

  my_file.close();
  return 0;
}
