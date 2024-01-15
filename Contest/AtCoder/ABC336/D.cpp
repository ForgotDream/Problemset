#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[N], b[N];

int f[N], g[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  // memcpy(b, a, sizeof(b));
  // for (int i = 1; i <= n; i++) {
  //   int p = f[i - 1] + 1;
  //   if (b[i] >= p) b[i] = p, f[i] = p;
  //   else f[i] = b[i];
  // }
  // for (int i = 1; i <= n; i++) std::cerr << f[i] << " \n"[i == n];
  //
  // memcpy(b, a, sizeof(b));
  // for (int i = n; i >= 1; i--) {
  //   int p = g[i + 1] + 1;
  //   if (b[i] >= p) b[i] = p, g[i] = p;
  //   else g[i] = b[i];
  // }
  // for (int i = 1; i <= n; i++) std::cerr << g[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
