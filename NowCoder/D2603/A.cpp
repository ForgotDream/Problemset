#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned int;

int p[30][2][2];
int f[31][2];

void solve() {
  int n;
  std::cin >> n;

  for (int i = 0, a; i < n; i++) {
    std::cin >> a;
    for (int idx = 0; idx < 30; idx++) {
      int u = (a >> idx) & 1;
      int v = idx ? ((a >> (idx - 1)) & 1) : 0;
      p[idx][u][v]++;
    }
  }

  int m;
  std::cin >> m;

  for (int i = 1; i <= 30; i++) f[i][1] = 1;

  for (int typ, x; m; m--) {
    std::cin >> typ >> x;

    for (int idx = 1; idx <= 30; idx++) {
      int u = (x >> (idx - 1)) & 1;

      if (typ == 1) f[idx][0] &= u, f[idx][1] &= u;
      else if (typ == 2) f[idx][0] |= u, f[idx][1] |= u;
      else f[idx][0] ^= u, f[idx][1] ^= u;
    }

    i64 ans = 0;
    for (int idx = 0; idx < 30; idx++) {
      for (int u = 0; u < 2; u++) {
        for (int v = 0; v < 2; v++) {
          if (f[idx + 1][u] == 1 && f[idx][v] == 0) ans += p[idx][u][v];
        }
      }
    }
    std::cout << ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
