#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 105;

int n, q, p[N];

void solve() {
  std::cin >> n;
  for (int i = 1, u; i <= n; i++) std::cin >> u, p[u] = i;
  std::cin >> q;
  for (int u, v; q; q--) {
    std::cin >> u >> v;
    if (p[u] < p[v]) std::cout << u << "\n";
    else std::cout << v << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
