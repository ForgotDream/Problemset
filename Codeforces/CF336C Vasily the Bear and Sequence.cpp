/**
 * @file    CF336C Vasily the Bear and Sequence.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-31
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1 << 30; i; i >>= 1) {
    int val = 0;
    std::vector<int> ans;
    for (int j = 1; j <= n; j++) {
      if (a[j] & i) {
        if (!ans.empty()) val &= a[j];
        else val = a[j];
        ans.push_back(a[j]);
      }
    }
    if (val % i == 0 && !ans.empty()) {
      std::cout << ans.size() << "\n";
      for (auto v : ans) std::cout << v << " ";
      std::cout << "\n";
      return;
    }
  }
  std::cout << -1 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}