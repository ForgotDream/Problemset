#include <iostream>

using i64 = long long;

constexpr int N = 10, M = 2e5 + 50, mod = 1e9 + 7;
int n, m;
int f[M][N];
void solve() {
  std::cin >> n >> m;
  int ans = 0;
  while (n) {
    (ans += f[m][n % 10]) %= mod;
    n /= 10;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);
  for (int i = 0; i <= 9; i++) f[0][i] = 1;
  for (int i = 1; i <= 2e5; i++) {
    for (int j = 0; j <= 8; j++) {
      f[i][j] = f[i - 1][j + 1];
    }
    f[i][9] = (f[i - 1][0] + f[i - 1][1]) % mod;
  }
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}