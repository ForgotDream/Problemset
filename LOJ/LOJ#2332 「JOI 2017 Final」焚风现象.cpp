/**
 * @file    LOJ#2332 「JOI 2017 Final」焚风现象.cpp
 * @author  ForgotDream
 * @brief   查分
 * @date    2023-10-10
 */
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, q, s, t;
i64 a[N], d[N];
inline i64 calc(int i) {
  if (i == n) return 0ll;
  if (d[i + 1] == 0) return 0ll;
  else if (d[i + 1] > 0) return d[i + 1] * (-s);
  else return (-d[i + 1]) * t;
}
void solve() {
  std::cin >> n >> q >> s >> t;
  for (int i = 0; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) d[i] = a[i] - a[i - 1];
  i64 ans = 0;
  for (int i = 0; i < n; i++) ans += calc(i);
  for (int i = 1, l, r, x; i <= q; i++) {
    std::cin >> l >> r >> x;
    ans -= calc(l - 1), ans -= calc(r);
    d[l] += x, d[r + 1] -= x;
    ans += calc(l - 1), ans += calc(r);
    std::cout << ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
