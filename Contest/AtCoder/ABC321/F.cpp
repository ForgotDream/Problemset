#include <iostream>

using i64 = long long;

constexpr int N = 5050, mod = 998244353;
int q, k, f[N][N], n = 5000;
void solve() {
  std::cin >> q >> k;
  for (int _ = 1; _ <= q; _++) {
    char opt;
    int u;
    std::cin >> opt >> u;
    f[0][0] = 1;
    if (opt == '+') {
      for (int i = 0; i <= n; i++) {
        if (i >= u) f[_][i] = (f[_ - 1][i] + f[_ - 1][i - u]) % mod;
        else f[_][i] = f[_ - 1][i];
      }
    } else {
      for (int i = 0; i <= n; i++) {
        if (i >= u) f[_][i] = (f[_ - 1][i] - f[_][i - u] + mod) % mod;
        else f[_][i] = f[_ - 1][i];
      }
    }
    std::cout << f[_][k] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
