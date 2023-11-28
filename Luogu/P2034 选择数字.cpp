/**
 * @file    P2034 选择数字.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-26
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e5 + 50;
int n, k, a[N];
i64 f[N][2], s[N];
void solve() {
  std::cin >> n >> k;
  std::deque<int> dq;
  dq.push_back(0);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i], s[i] = s[i - 1] + a[i];
    f[i][0] = std::max(f[i - 1][0], f[i - 1][1]);
    while (!dq.empty() && dq.front() < i - k) dq.pop_front();
    f[i][1] = f[dq.front()][0] + s[i] - s[dq.front()];
    while (!dq.empty() && f[dq.back()][0] - s[dq.back()] < f[i][0] - s[i]) dq.pop_back();
    dq.push_back(i);
  }
  std::cout << std::max(f[n][0], f[n][1]) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
