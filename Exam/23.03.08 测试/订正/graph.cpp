#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;
  
  std::vector<int> a(n);
  for (auto &i : a) {
    std::cin >> i;
  }

  double ans = 0;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    ans = std::max(ans, double(a[u - 1] + a[v - 1]) / w);
  }

  std::cout << std::fixed << std::setprecision(2) << ans << "\n";

  return 0;
}