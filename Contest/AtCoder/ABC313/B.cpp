#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 55;
int n, m, deg[N];
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    deg[v]++;
  }
  int ans = -1;
  for (int i = 1; i <= n; i++) {
    if (!deg[i] && ans == -1) ans = i;
    else if (!deg[i] && ans != -1) return std::cout << -1 << "\n", 0;
  }
  std::cout << ans << "\n";
  return 0;
}