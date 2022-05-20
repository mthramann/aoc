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
using ::std::ostream;
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

class Num;

class Num {
 public:
  optional<int> num;
  unique_ptr<Num> left;
  unique_ptr<Num> right;
  Num* parent;

  bool explode();

  Num(const string& str, int& ind) {
    if (str[ind] == '[') {
      ind++;
      left = unique_ptr<Num>(new Num(str, ind));
      ind++;  // comma
      right = unique_ptr<Num>(new Num(str, ind));
      ind++;  // closing bracket
      left->parent = this;
      right->parent = this;
    } else {
      num = 0;
      while (str[ind] >= '0' && str[ind] <= '9') {
        num = num.value() * 10;
        num = num.value() + (str[ind] - '0');
        ind++;
      }
    }
    parent = nullptr;
  }

  void add(const string& str) {
    unique_ptr<Num> l = unique_ptr<Num>(new Num());
    left->parent = l.get();
    right->parent = l.get();
    l->left = std::move(left);
    l->right = std::move(right);
    l->parent = this;
    left = std::move(l);
    int ind = 0;
    right = unique_ptr<Num>(new Num(str, ind));
    right->parent = this;
    this->reduce();
  }

  bool split() {
    stack<Num*> s;
    s.push(this);
    while (!s.empty()) {
      Num* curr = s.top();
      s.pop();
      if (curr->num.has_value() && curr->num.value() > 9) {
        int num = curr->num.value();
        curr->num.reset();
        curr->left = unique_ptr<Num>(new Num());
        curr->left->parent = curr;
        curr->left->num = num / 2;
        curr->right = unique_ptr<Num>(new Num());
        curr->right->parent = curr;
        curr->right->num = (num / 2) + (num % 2);
        return true;
      }
      if (curr->right != nullptr) s.push(curr->right.get());
      if (curr->left != nullptr) s.push(curr->left.get());
    }
    return false;
  }

  void reduce() {
    bool action = false;
    do {
      action = explode() || split();
    } while (action);
  }

  unsigned long magnitude() const {
    if (num.has_value()) return num.value();
    return 3 * left->magnitude() + 2 * right->magnitude();
  }

 private:
  Num(){};
};

ostream& operator<<(ostream& os, const Num& n) {
  if (n.num.has_value()) {
    os << n.num.value();
  } else if (n.left != nullptr && n.right != nullptr) {
    os << "[" << *(n.left) << "," << *(n.right) << "]";
  }

  return os;
}

Num* rightSuccessor(Num* curr) {
  Num* parent = curr->parent;
  while (parent != nullptr && parent->right.get() == curr) {
    curr = parent;
    parent = curr->parent;
  }
  if (parent == nullptr) return nullptr;
  if (parent->right->num.has_value()) return parent->right.get();
  curr = parent->right.get();
  while (!curr->num.has_value()) {
    curr = curr->left.get();
  }
  return curr;
}

Num* leftSuccessor(Num* curr) {
  Num* parent = curr->parent;
  while (parent != nullptr && parent->left.get() == curr) {
    curr = parent;
    parent = curr->parent;
  }
  if (parent == nullptr) return nullptr;
  if (parent->left->num.has_value()) return parent->left.get();
  curr = parent->left.get();
  while (!curr->num.has_value()) {
    curr = curr->right.get();
  }
  return curr;
}

bool Num::explode() {
  if (num.has_value()) return false;
  //  cout << *this << endl;
  stack<pair<Num*, int>> s;
  Num* curr = this;
  s.push({this, 0});
  while (!s.empty()) {
    auto [curr, depth] = s.top();
    s.pop();

    if (!curr->num.has_value() && curr->left->num.has_value() &&
        curr->right->num.has_value() && depth > 3) {
      Num* t = leftSuccessor(curr);
      if (t != nullptr) {
        t->num = t->num.value() + curr->left->num.value();
      }
      t = rightSuccessor(curr);
      if (t != nullptr) {
        t->num = t->num.value() + curr->right->num.value();
      }
      curr->left = nullptr;
      curr->right = nullptr;
      curr->num = 0;

      return true;
    }

    if (curr->right != nullptr && !curr->right->num.has_value())
      s.push({curr->right.get(), depth + 1});
    if (curr->left != nullptr && !curr->left->num.has_value())
      s.push({curr->left.get(), depth + 1});
  }
  return false;
}

std::vector<int> split(const std::string& s, char delimiter) {
  std::vector<int> tokens;
  std::string token;
  std::stringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}

int main(int argc, char* argv[]) {
  std::fstream my_file;
  vector<string> nums;
  my_file.open("day18.input", std::ios::in);
  if (!my_file) {
    std::cout << "No such file";
  } else {
    string line;
    while (!my_file.eof()) {
      getline(my_file, line);
      if (line.empty()) continue;
      nums.push_back(line);
    }
  }

  unsigned long max_mag = 0;
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      int r = 0;
      Num copy1(nums[i], r);
      copy1.add(nums[j]);
      max_mag = std::max(max_mag, copy1.magnitude());
      r = 0;
      Num copy2(nums[j], r);
      copy2.add(nums[i]);
      max_mag = std::max(max_mag, copy2.magnitude());
    }
  }

  cout << max_mag << endl;
  my_file.close();
  return 0;
}
