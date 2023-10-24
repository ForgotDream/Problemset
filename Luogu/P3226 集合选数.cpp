/**
 * @file    P3226 集合选数.cpp
 * @author  ForgotDream
 * @brief   Bitwise DP + Constructive Algorithms
 * @date    2023-05-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace Helper {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}

void debug(const std::string &s) {
  std::cerr << s << "\n";
  return;
}
}

constexpr i64 MOD = 1e9 + 1;

std::vector<std::vector<int>> init(const int &num, const int &n, std::vector<bool> &used) {
  std::vector<std::vector<int>> mat;
  int curRow = num, cntRow = 0;

  while (true) {
    if (curRow > n) {
      break;
    }
    mat.emplace_back(0);
    int curCol = curRow;
    while (true) {
      if (curCol > n) {
        break;
      }
      mat[cntRow].push_back(curCol);
      used[curCol] = true;
      curCol *= 2;
    }
    curRow *= 3;
    cntRow++;
  }

  return mat;
}

i64 calc(const int &num, const std::vector<std::vector<int>> &mat) {
  static constexpr int MAX = (1 << 18) - 1;
  static std::bitset<MAX> table;
  if (num == 1) {
    for (int i = 0; i < table.size(); i++) {
      table[i] = !((i << 1) & i);
    }
  }
  
  std::vector f(mat.size(), std::vector<i64>());
  for (int i = 0; i < f.size(); i++) {
    f[i].resize(1 << mat[i].size());
  }

  for (int i = 0; i < f[0].size(); i++) {
    f[0][i] = table[i];
  }

  for (int i = 1; i < f.size(); i++) {
    for (int j = 0; j < f[i].size(); j++) {
      if (!table[j]) {
        continue;
      }
      for (int k = 0; k < f[i - 1].size(); k++) {
        if (!table[k]) {
          continue;
        }
        if ((k & j) == 0) {
          (f[i][j] += f[i - 1][k]) %= MOD;
        }
      }
    }
  }

  return std::accumulate(f[f.size() - 1].begin(), f[f.size() - 1].end(), 0ll);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<bool> used(n + 1);
  i64 ans = 1;
  for (int i = 1; i <= n; i++) {
    if (!used[i]) {
      auto mat = init(i, n, used);
      (ans *= calc(i, mat)) %= MOD;
    }
  }

  std::cout << ans << "\n";

  return 0;
}