#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using i64 = long long;

int main() {
  // freopen("eat.in", "r", stdin);
  // freopen("eat.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n;
  std::vector<int> num(4);
  std::cin >> n;
  for (auto &i : num) {
    std::cin >> i;
  }
  
  std::vector<int> l[4];
  for (int i = 0; i < 4; i++) {
    l[i].resize(num[i]);
    for (auto &j : l[i]) {
      std::cin >> j;
    }
  }
  
  std::vector<i64> lo(n + 1, 0), hi(n + 1, 0);
  for (auto &i : l[0]) {
    for (auto &j : l[1]) {
      if (i + j > n) {
        continue;
      }
      lo[i + j]++;
    }
  }
  for (auto &i : l[2]) {
    for (auto &j : l[3]) {
      if (i + j > n) {
        continue;
      }
      hi[i + j]++;
    }
  }
  
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    lo[i] += lo[i - 1];
  }
  for (int i = 0; i <= n; i++) {
    ans += hi[i] * lo[n - i];
  }
  
  std::cout << ans << "\n";
  
  return 0;
}