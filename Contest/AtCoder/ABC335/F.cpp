#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50, M = 500, mod = 998244353;
int n, a[N];
i64 f[N], s[M][M];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  int blk = std::sqrt(n);

  f[1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < blk; j++) {
      f[i] += s[j][i % j];
      f[i] %= mod;
    }
    if (a[i] >= blk) {
      for (int j = 1; i + j * a[i] <= n; j++) {
        f[i + j * a[i]] += f[i];
        f[i + j * a[i]] %= mod;
      }
    } else {
      s[a[i]][i % a[i]] += f[i];
      s[a[i]][i % a[i]] %= mod;
    }
  }

  i64 ans = 0;
  for (int i = 1; i <= n; i++) (ans += f[i]) %= mod;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
