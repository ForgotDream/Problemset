/**
 * @file    CF71D Solitaire.cpp
 * @author  ForgotDream
 * @brief   Simulation
 * @date    2023-09-05
 */
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <tuple>

using i64 = long long;
using ti4 = std::tuple<int, int, int, int>;

constexpr int N = 20;
constexpr char fir[] = {'2', '3', '4', '5', '6', '7', '8',
                        '9', 'T', 'J', 'Q', 'K', 'A'};
constexpr char sec[] = {'C', 'D', 'H', 'S'};
int n, m;
std::string a[N][N];
int jx[3], jy[3], cnt = 0;
std::set<std::string> rst;
bool check(int x, int y) {
  std::set<char> col, val;
  bool flg = true;
  for (int i = x; i <= x + 2; i++) {
    for (int j = y; j <= y + 2; j++) {
      col.insert(a[i][j][1]);
      if (val.count(a[i][j][0])) flg = false;
      else val.insert(a[i][j][0]);
      if (!flg && col.size() > 1) {
        return false;
      }
    }
  }
  return true;
}
ti4 find() {
  for (int x1 = 1; x1 <= n - 2; x1++) {
    for (int y1 = 1; y1 <= m - 2; y1++) {
      for (int x2 = 1; x2 <= n - 2; x2++) {
        for (int y2 = 1; y2 <= m - 2; y2++) {
          if (x2 <= x1 && y2 <= y1) continue;
          if (std::max(x2 - x1, y2 - y1) < 3) continue;
          if (check(x1, y1) && check(x2, y2)) return std::tuple(x1, y1, x2, y2);
        }
      }
    }
  }
  return std::tuple(-1, -1, -1, -1);
}
void solve() {
  std::cin >> n >> m;
  for (auto c1 : fir) {
    for (auto c2 : sec) rst.insert(std::string(1, c1) + c2);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::string &t = a[i][j];
      std::cin >> t;
      if (t[0] == 'J' && std::isdigit(t[1])) {
        jx[t[1] - '0'] = i, jy[t[1] - '0'] = j;
        cnt++;
      }
      rst.erase(t);
    }
  }
  if (cnt == 0) {
    auto [x1, y1, x2, y2] = find();
    if (x1 == -1) {
      std::cout << "No solution.\n";
    } else {
      std::cout << "Solution exists.\n";
      std::cout << "There are no jokers.\n";
      std::cout << "Put the first square to (" << x1 << ", " << y1 << ").\n";
      std::cout << "Put the second square to (" << x2 << ", " << y2 << ").\n";
    }
  } else if (cnt == 1) {
    int d = 1;
    if (jx[2]) d = 2;
    for (const auto &i : rst) {
      a[jx[d]][jy[d]] = i;
      auto [x1, y1, x2, y2] = find();
      if (x1 == -1) {
        continue;
      } else {
        std::cout << "Solution exists.\n";
        std::cout << "Replace J" << d << " with " << i << ".\n";
        std::cout << "Put the first square to (" << x1 << ", " << y1 << ").\n";
        std::cout << "Put the second square to (" << x2 << ", " << y2 << ").\n";
        return;
      }
    }
    std::cout << "No solution.\n";
  } else {
    for (const auto &i : rst) {
      for (const auto &j : rst) {
        if (i == j) continue;
        a[jx[1]][jy[1]] = i, a[jx[2]][jy[2]] = j;
        auto [x1, y1, x2, y2] = find();
        if (x1 == -1) {
          continue;
        } else {
          std::cout << "Solution exists.\n";
          std::cout << "Replace J1 with " << i << " and J2 with " << j << ".\n";
          std::cout << "Put the first square to (" << x1 << ", " << y1
                    << ").\n";
          std::cout << "Put the second square to (" << x2 << ", " << y2
                    << ").\n";
          return;
        }
      }
    }
    std::cout << "No solution.\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}