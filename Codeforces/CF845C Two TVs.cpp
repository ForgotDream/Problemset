/**
 * @file    CF845C Two TVs.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-08-25
 */
#include <algorithm>
#include <iostream>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n;
pii a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i].first >> a[i].second;
  std::sort(a + 1, a + n + 1, [&](auto lhs, auto rhs) {
    return lhs.first < rhs.first ||
           (lhs.first == rhs.first && lhs.second > rhs.second);
  });
  int p[2] = {-1, -1}, cur = 0;
  for (int i = 1; i <= n; i++) {
    auto [l, r] = a[i];
    if (l > p[cur]) {
      p[cur] = r;
    } else {
      cur ^= 1;
      if (p[cur] < l) p[cur] = r;
      else return void(std::cout << "NO\n");
    }
  }
  std::cout << "YES\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}