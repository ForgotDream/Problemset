/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-04-23
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace MyFile {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector v(std::vector<int>(100, 0));

  int n;
  std::cin >> n;

  std::vector<int> fa(n + 1), num(n), dep(n + 1);
  for (int i = 2; i <= n; i++) {
    std::cin >> fa[i];
    num[dep[i] = dep[fa[i]] + 1]++;
  }

  int block = std::sqrt(n);

  for (int i = 1; i <= block; i++) {
    
  }

  return 0;
}