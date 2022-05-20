#include <string>
#include <unordered_map>
#include <pair>
#include <queue>
#include <iostream>

using ::std::string;
using ::std::unordered_map;
using ::std::pair;
using ::std::queue;
using ::std::cout;
using ::std::endl;

int main() {
  int costs[] = {1, 10, 100, 1000};
  // Inds 2, 4, 6, 8 connect to 11, 13, 15, 17 respectively.
  const string init_state = "...........ABDCBDCA";
  const string end_state = "...........AABCCDD";
  unordered_map<string, int> min_costs;
  min_costs[init_state] = 0;
  queue<pair<string, int>> states;
  states.push({init_state, 0});
  while (!states.empty()) {
    auto [state, cost] = states.top();
    states.pop();
    if (min_costs.contains(state) && min_costs[state] <= cost) {
      continue;
    }
    min_costs[state] = cost;
    for (int i = 0; i < 11; i++) { // Walk the hallway.
      if (state[i] == 'A' && (state[12] == '.' || state[12] == 'A')) {
          int steps = (i - 2) < 0 ? 2 - i : i - 2;
          string new_state = state;
          new_state[i] = '.';
          if (state[12] == '.') {
            steps += 2;
            new_state[12] = 'A';
          } else {
            steps++;
            new_state[11] = 'A';
          }
          states.push({new_state, cost + steps});
      } else if (state[i] == 'B' && (state[14] == '.' || state[14] == 'B')) {
          int steps = (i - 4) < 0 ? 4 - i : i - 4;
          string new_state = state;
          new_state[i] = '.';
          if (state[14] == '.') {
            steps += 2;
            new_state[14] = 'B';
          } else {
            steps++;
            new_state[13] = 'B';
          }
          states.push({new_state, cost + (steps * 10)});
      } else if (state[i] = 'C' && (state[16] == '.' || state[16] == 'C')) {
          int steps = (i - 6) < 0 ? 6 - i : i - 6;
          string new_state = state;
          new_state[i] = '.';
          if (state[16] == '.') {
            steps += 2;
            new_state[16] = 'C';
          } else {
            steps++;
            new_state[15] = 'C';
          }
          states.push({new_state, cost + (steps * 100)});
        } else if (state[i] == 'D' && (state[18] == '.' || state[18] == 'D')) {
          int steps = (i - 8) < 0 ? 8 - i : i - 8;
          string new_state = state;
          new_state[i] = '.';
          if (state[18] == '.') {
            steps += 2;
            new_state[18] = 'D';
          } else {
            steps++;
            new_state[18] = 'D';
          }
          states.push({new_state, cost + (steps * 1000)});
        }
        }
            // Check leaving the rooms.
      int a_room = state[11] == '.' ? 12 : 11;
      int b_room = state[13] == '.' ? 14 : 13;
      int c_room = state[15] == '.' ? 16 : 15;
      int d_room = state[17] == '.' ? 18 : 17;

      string new_state = state;
      if (state[12] != 'A' || ) {
        new_state[a_room] = '.';
        int left = 2, right = 2;
        while (left > 0 && state[left - 1] == '.') {
          left--;
        }
        while (right < 11 && state[right] == '.') {
          right++;
        }
        for (int i = left; i < right; i++) {
          if (i != 10 && (i % 2 == 0)) { // Can't stop outside room.
            continue;
          }

          int steps = i - 2 < 0 ? 2 - i : i - 2;
          steps++;
          if (state[11] == '.') steps++;
          new_state[i] = state[a_room];
          states.push({new_state, cost + (steps * costs[state[a_room] - 'A'])});
        }
      }

      if (state[b_room] != 'B') {
        new_state[b_room] = '.';
        int left = 4, right = 4;
        while (left > 0 && state[left - 1] == '.') {
          left--;
        }
        while (right < 11 && state[right] == '.') {
          right++;
        }
        for (int i = left; i < right; i++) {
          if (i != 10 && (i % 2 == 0)) { // Can't stop outside room.
            continue;
          }

          int steps = i - 4 < 0 ? 4 - i : i - 4;
          steps++;
          if (state[13] == '.') steps++;
          new_state[i] = state[b_room];
          states.push({new_state, cost + (steps * costs[state[b_room] - 'A'])});
        }
      }

      if (state[c_room] != 'C') {
        new_state[c_room] = '.';
        int left = 6, right = 6;
        while (left > 0 && state[left - 1] == '.') {
          left--;
        }
        while (right < 11 && state[right] == '.') {
          right++;
        }
        for (int i = left; i < right; i++) {
          if (i != 10 && (i % 2 == 0)) { // Can't stop outside room.
            continue;
          }

          int steps = i - 6 < 0 ? 6 - i : i - 6;
          steps++;
          if (state[15] == '.') steps++;
          new_state[i] = state[c_room];
          states.push({new_state, cost + (steps * costs[state[c_room] - 'A'])});
        }
      }

      if (state[d_room] != 'D') {
        new_state[droom] = '.';
        int left = 8, right = 8;
        while (left > 0 && state[left - 1] == '.') {
          left--;
        }
        while (right < 11 && state[right] == '.') {
          right++;
        }
        for (int i = left; i < right; i++) {
          if (i != 10 && (i % 2 == 0)) { // Can't stop outside room.
            continue;
          }

          int steps = i - 8 < 0 ? 8 - i : i - 8;
          steps++;
          if (state[17] == '.') steps++;
          new_state[i] = state[d_room];
          states.push({new_state, cost + (steps * costs[state[d_room] - 'A'])});
        }
      }
  }

  cout << min_costs[end_state] << endl;
  return 0;
}

      string new_state = state;
      string new_state = state;


      string new_state = state;

      string new_state = state;
