#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>

using i64 = long long;

i64 k, a, b;
int len;
std::set<i64> ans;
void dfs(int u, int cur, int f) {
  if (u == len + 1) {
    i64 n = k * f, cpy = n;
    i64 tmp = 0;
    while (n) tmp += (n % 10) * (n % 10), n /= 10;
    if (tmp != f) return;
    if (cpy >= a && cpy <= b) ans.insert(cpy);
    return;
  }
  for (int i = cur; i <= 9; i++) {
    dfs(u + 1, i, f + i * i);
  }
}
void solve() {
  std::cin >> k >> a >> b;
  auto cpy = b;
  while (cpy) len++, cpy /= 10;
  dfs(1, 0, 0);
  std::cout << ans.size() << "\n";
}

int main() {
  std::freopen("equation.in", "r", stdin);
  std::freopen("equation.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
