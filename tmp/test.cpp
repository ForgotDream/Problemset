#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 15, M = 105, mod = 1e9 + 7;
int n, p[M], a[M][N];
i64 f[M][1 << N];
void solve() {
  std::cin >> n;
  std::cin.get();
  for (int i = 1; i <= 100; i++) p[i] = 0;
  for (int i = 0; i < n; i++) {
    std::string s;
    std::getline(std::cin, s);
    std::stringstream ss(s);
    int u;
    while (ss >> u) a[u][++p[u]] = i;
  }
  int mask = (1 << n) - 1;
  memset(f, 0, sizeof(f)), f[0][0] = 1;
  for (int i = 1; i <= 100; i++) {
    for (int j = 0; j <= mask; j++) {
      f[i][j] = f[i - 1][j];
      for (int k = 1; k <= p[i]; k++) {
        int u = a[i][k];
        if (!(j & (1 << u))) continue;
        f[i][j] = (f[i][j] + f[i - 1][j ^ (1 << u)]) % mod;
      }
    }
  }
  std::cout << f[100][mask] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}

