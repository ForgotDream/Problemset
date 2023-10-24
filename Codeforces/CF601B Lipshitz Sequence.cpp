/**
 * @file    CF601B Lipshitz Sequence.cpp
 * @author  ForgotDream
 * @brief   单调栈
 * @date    2023-08-30
 */
#include <cmath>
#include <iostream>
#include <stack>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, q, a[N], b[N];
int lp[N], rp[N];
void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) b[i] = std::abs(a[i + 1] - a[i]);
  for (int i = 1, l, r; i <= q; i++) {
    std::cin >> l >> r, r--;
    for (int j = l; j <= r; j++) lp[j] = l - 1, rp[j] = r + 1;
    std::stack<int> s;
    for (int j = l; j <= r; j++) {
      while (!s.empty() && b[s.top()] < b[j]) {
        rp[s.top()] = j;
        s.pop();
      }
      if (!s.empty()) lp[j] = s.top();
      s.push(j);
    }
    i64 ans = 0;
    for (int j = l; j <= r; j++) {
      ans += 1ll * b[j] * (j - lp[j]) * (rp[j] - j);
    }
    std::cout << ans << "\n";
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