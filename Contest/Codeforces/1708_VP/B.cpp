#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
int t, n, l, r;
int cnt, a[N];
void solve() {
  std::cin >> n >> l >> r;
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    int cur = i;
    cur = std::ceil(1. * l / i) * i;
    if (cur > r) return void(std::cout << "NO\n");
    a[++cnt] = cur;
  }
  std::cout << "YES\n";
  for (int i = 1; i <= n; i++) std::cout << a[i] << " \n"[i == n];
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}