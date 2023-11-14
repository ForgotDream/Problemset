#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e5 + 50, M = 205, mod = 998244353;
int n, w[N], q;
i64 f[M];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> w[i];
  std::cin >> q;
  for (int l, r, m; q; q--) {
    std::cin >> l >> r >> m;
    memset(f, 0, sizeof(f)), f[0] = 1;
    for (int j = l; j <= r; j++) {
      for (int k = m; k >= w[j]; k--) (f[k] += f[k - w[j]]) %= mod;
    }
    std::cout << f[m] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
