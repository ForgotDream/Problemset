/**
 * @file    P5980 [PA2019] Herbata.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
int t, n;
std::pair<int, int> a[N], b[N];
i64 s1, s2;
void solve() {
  std::cin >> n;
  s1 = s2 = 0;
  for (int i = 1, l, a, b; i <= n; i++) {
    std::cin >> l >> a >> b;
    ::a[i] = std::make_pair(a, l), ::b[i] = std::make_pair(b, l);
    s1 += 1ll * l * a, s2 += 1ll * l * b;
  }
  if (s1 != s2) return void(std::cout << "NIE\n");
  std::sort(a + 1, a + n + 1), std::sort(b + 1, b + n + 1);
  int p = 1, q = 1;
  i64 sum = 0;
  bool flg = true;
  while (p <= n) {
    int cnt = std::min(a[p].second, b[q].second);
    sum -= 1ll * cnt * (a[p].first - b[q].first);
    if (sum < 0) {
      flg = false;
      break;
    }
    a[p].second -= cnt, b[q].second -= cnt;
    if (!a[p].second) p++;
    if (!b[q].second) q++;
  }
  if (flg && sum == 0) std::cout << "TAK\n";
  else std::cout << "NIE\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}