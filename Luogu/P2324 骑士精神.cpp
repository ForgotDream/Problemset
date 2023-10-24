/**
 * @file    P2324 骑士精神.cpp
 * @author  ForgotDream
 * @brief   IDA*
 * @date    2023-05-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

constexpr int d[] = { -11, -9, -7, -3, 3, 7, 9, 11 };
// constexpr int d[] = { -10, -8, -6, -2, 2, 6, 8, 10 };

void solve() {
  std::string s, t = "111110111100*110000100000";
  for (int i = 0; i < 5; i++) {
    std::string c;
    std::cin >> c;
    s += c;
  }

  auto evaluate = [&](const std::string &u) -> int {
    int res = 0;
    for (int i = 0; i < 5 * 5; i++) {
      if (t[i] != u[i]) {
        res++;
      }
    }
    return res;
  };

  std::function<bool(std::string, int, int)> dfs = 
  [&](const std::string &u, int dep, int max) -> bool {
    if (dep == max) {
      // std::cerr << dep << "\t" << u << "\n";
      return (evaluate(u) == 0);
    }
    int x = std::find(u.begin(), u.end(), '*') - u.begin();
    bool flg = false;
    for (int i = 0; i < 8; i++) {
      int dx = x + d[i];
      if (dx < 0 || dx >= 5 * 5) {
        continue;
      } else if (!((std::abs(dx / 5 - x / 5) == 1 && std::abs(dx % 5  - x % 5) == 2) || 
                   (std::abs(dx / 5 - x / 5) == 2 && std::abs(dx % 5  - x % 5) == 1))) {
        continue;
      }
      std::string v = u;
      std::swap(v[x], v[dx]);
      // if (clk != 1 && max == 14) std::cerr << u << " & " << v << "\n";
      if (evaluate(v) + dep <= max) {
        flg |= dfs(v, dep + 1, max);
      }
    }
    return flg;
  };

  for (int i = 0; i <= 15; i++) {
    if (dfs(s, 0, i)) {
      std::cout << i << "\n";
      return;
    }
  }

  std::cout << -1 << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}