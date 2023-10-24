/**
 * @file    LOJ#10021 Addition Chains.cpp
 * @author  ForgotDream
 * @brief   IDDFS
 * @date    2023-03-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

bool dfs(int cur, int tgt, int dep) {
  static std::vector<int> a = {1};
  if (a[cur - 1] == tgt) {
    for (auto i : a) {
      std::cout << i << " ";
    }
    std::cout << "\n";
    a.resize(1);
    a[0] = 1;
    return true;
  } else if (a[cur - 1] > tgt) {
    return false;
  } else if (cur > dep) {
    return false;
  }

  for (int i = cur - 1; i >= 0; i--) {
    for (int j = cur - 1; j >= 0; j--) {
      if ((a[i] + a[j]) << (dep - cur) < tgt) {
        continue;
      }
      a.push_back(a[i] + a[j]);
      if (dfs(cur + 1, tgt, dep)) {
        return true;
      }
      a.pop_back();
    }
  }

  return false;
}

void solve(int tgt) {
  for (int i = 1; ; i++) {
    if (dfs(1, tgt, i)) {
      break;
    }
  }
  return;
}

signed main() {
  // #ifndef DONLINE_JUDGE
  // freopen("tmp.in", "r", stdin);
  // freopen("tmp.out", "w", stdout);
  // #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  while (std::cin >> n && n) {
    solve(n);
  }

  return 0;
}