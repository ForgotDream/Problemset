#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned int;

constexpr int mod = 998244353;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> p(n), q(n);
  bool flg = true;

  for (int i = 0; i < n; i++) {
    std::cin >> p[i], p[i]--;
    q[p[i]] = i;
    if (i != p[i]) flg = false;
  }

  if (flg) {
    i64 ans = 1;
    for (int i = 1; i <= n; i++) ans = ans * i % mod;
    std::cout << ans << "\n";
    return;
  }
  
  std::vector<u32> g(n);
  for (int u = 0; u < n; u++) {
    for (int v = u + 1; v < n; v++) {
      if (q[u] > q[v]) g[u] |= (1 << v);
    }
  }

  std::vector<int> f(1 << n);
  f[0] = 1;
  
  u32 mask = (1 << n) - 1;

  for (u32 cur = 0; cur <= mask; cur++) {
    u32 rst = mask ^ cur;

    while (rst) {
      u32 u = std::countr_zero(rst);

      if ((cur & g[u]) == g[u]) {
        u32 nxt = cur | (1 << u);
        f[nxt] = (f[nxt] + f[cur]) % mod;
      }

      rst &= rst - 1;
    }
  }

  int ans = 2 * f[mask] % mod;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
