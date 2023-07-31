/**
 * @file    P2804 神秘数字.cpp
 * @author  ForgotDream
 * @brief   CDQ
 * @date    2023-07-31
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50, mod = 92084931;
int n, k;
i64 ans, a[N], s[N];

void solve(int l, int r) {
  if (l == r) {
    if (a[l] > 0) ans++;
    return;
  }
  int mid = (l + r) >> 1;
  solve(l, mid), solve(mid + 1, r);

  std::vector<i64> lv, rv;
  for (int i = l; i <= mid; i++) lv.push_back(s[mid] - s[i - 1]);
  for (int i = mid + 1; i <= r; i++) rv.push_back(s[i] - s[mid]);
  std::sort(lv.begin(), lv.end());
  std::sort(rv.begin(), rv.end(), std::greater<i64>());

  int i = 0, j = 0;
  while (i < lv.size()) {
    while (j < rv.size() && lv[i] + rv[j] > 0) j++;
    i++, (ans += j) %= mod;
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);  

  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) 
    std::cin >> a[i], a[i] -= k, s[i] = a[i] + s[i - 1];
  solve(1, n);
  std::cout << ans % mod << "\n";

  return 0;
}
