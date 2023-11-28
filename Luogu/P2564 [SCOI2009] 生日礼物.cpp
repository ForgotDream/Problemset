/**
 * @file    P2564 [SCOI2009] 生日礼物.cpp
 * @author  ForgotDream
 * @brief   Monotone Queue
 * @date    2023-11-27
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 1e6 + 50, K = 65;
int n, k, m, cnt[K];
pii a[N];
void solve() {
  std::cin >> n >> k;
  n = 0;
  for (int i = 1, u, p; i <= k; i++) {
    std::cin >> u;
    for (int j = 1; j <= u; j++) std::cin >> p, a[++n] = {p, i};
    std::inplace_merge(a + 1, a + n - u + 1, a + n + 1);
  }
  a[n + 1] = {a[n].first + 1, 0};
  int p = 1, cur = 0, ans = INT_MAX;
  for (int i = 1; i <= n; i++) {
    while (p <= n && cur < k) cur += (++cnt[a[p++].second] == 1);
    if (cur == k) ans = std::min(ans, a[p - 1].first - a[i].first);
    // if (cur == k) std::cerr << a[i].first << " " << a[p - 1].first << "\n";
    cur -= (--cnt[a[i].second] == 0);
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
