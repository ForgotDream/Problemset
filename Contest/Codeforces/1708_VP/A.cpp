#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 105;
int t, n, a[N], b[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], b[i] = a[i];
  for (int i = 2; i <= n; i++) {
    if (a[i] % a[1] != 0) return void(std::cout << "NO\n");
  }
  std::cout << "YES\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}