#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include <iostream>

using i64 = long long;

int main() {
  freopen("zero.in", "r", stdin);
  freopen("zero.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n;
  std::cin >> n;
  
  std::vector<std::vector<int>> a(5, std::vector<int>(n));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
    }
  }
  
  std::unordered_set<int> sum1, sum2;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int cur = a[0][i] + a[1][j];
      sum1.insert(cur);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int cur = a[2][i] + a[3][j];
      sum2.insert(cur);
    }
  }
  
  for (auto i : sum1) {
    for (auto j : sum2) {
      for (auto k : a[4]) {
        if (i + j + k == 0) {
          std::cout << "YES\n";
          // std::cerr << 1.0 << " " << double(1.0 * std::clock() / CLOCKS_PER_SEC) << "\n";
          return 0;
        }
      }
    }
  }
  std::cout << "NO\n";
  
  // std::cerr << 2.0 << " " << double(1.0 * std::clock() / CLOCKS_PER_SEC) << "\n";
  
  return 0;
}
