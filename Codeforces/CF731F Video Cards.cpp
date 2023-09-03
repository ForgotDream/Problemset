/**
 * @file    CF731F Video Cards.cpp
 * @author  ForgotDream
 * @brief   前缀和
 * @date    2023-08-30
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[N], max;
i64 sum[N], ans, cnt[N];
int calc(int l, int r) {
  return sum[std::min(r, max)] - sum[l - 1];
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    max = std::max(max, a[i]), cnt[a[i]]++;
  }
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= max; i++) sum[i] = cnt[i] + sum[i - 1];
  for (int i = 1; i <= max; i++) {
    if (!cnt[i]) continue;
    i64 cur = 0;
    for (int j = 1; (j - 1) * i <= max; j++) {
      cur += 1ll * (j - 1) * i * calc((j - 1) * i, j * i - 1);
    }
    ans = std::max(ans, cur);
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}