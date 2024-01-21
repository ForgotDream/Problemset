#include <bits/stdc++.h>

using i64 = long long;

int h, w, k;

void solve() {
  std::cin >> h >> w >> k;
  std::vector a(h + 1, std::string());
  for (int i = 1; i <= h; i++) {
    std::cin >> a[i], a[i] = " " + a[i];
  }

  int ans = 1e9;

  for (int i = 1; i <= h; i++) {
    std::vector<int> f(w + 1), g(w + 1);

    for (int j = 1; j <= w; j++) {
      if (a[i][j] == 'x') f[j] = g[j] = 0;
      else if (a[i][j] == 'o') f[j] = f[j - 1] + 1, g[j] = g[j - 1] + 1;
      else f[j] = f[j - 1] + 1, g[j] = g[j - 1];

      if (f[j] > k) f[j] = k, g[j] -= (a[i][j - k] == 'o');

      if (f[j] == k) ans = std::min(ans, k - g[j]);
    }
  }

  for (int i = 1; i <= w; i++) {
    std::vector<int> f(h + 1), g(h + 1);

    for (int j = 1; j <= h; j++) {
      if (a[j][i] == 'x') f[j] = g[j] = 0;
      else if (a[j][i] == 'o') f[j] = f[j - 1] + 1, g[j] = g[j - 1] + 1;
      else f[j] = f[j - 1] + 1, g[j] = g[j - 1];

      if (f[j] > k) f[j] = k, g[j] -= (a[j - k][i] == 'o');

      if (f[j] == k) ans = std::min(ans, k - g[j]);
    }
  }

  if (ans == 1e9) std::cout << -1 << "\n";
  else std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
