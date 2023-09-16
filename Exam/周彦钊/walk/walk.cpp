#include <iostream>

using i64 = long long;

constexpr int N = 1e6 + 50;
i64 a, m, n, g[N];
i64 f(i64 num) {
  i64 res = 0;
  while (num) res = std::max(res, num % 10), num /= 10;
  return res;
}
void solve() {
  std::cin >> a >> m >> n;
  for (int i = 1; i < n; i++) a = (a + f(a)) % m;
  std::cout << a << "\n";
}

int main() {
  std::freopen("walk.in", "r", stdin);
  std::freopen("walk.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}