/**
 * @file    P2089 烤鸡.cpp
 * @author  ForgotDream
 * @brief   搜索
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

std::vector<std::vector<int>> dfs(int rst, int cur = 0) {
  static std::vector<int> a(10);
  
  if (cur == 10) {
    std::vector<std::vector<int>> res;
    if (!rst) {
      res.push_back(a);
    }
    return res;
  }

  std::vector<std::vector<int>> res;

  for (int i = 1; i <= 3; i++) {
    a[cur] = i;
    auto v = dfs(rst - i, cur + 1);
    for (auto j : v) {
      res.push_back(j);
    }
  }

  return res;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  auto v = dfs(n);
  std::cout << v.size() << "\n";
  for (auto i : v) {
    for (int j = 0; j < 10; j++) {
      std::cout << i[j] << " \n"[j == 9];
    }
  }

  return 0;
}