#include <iostream>

using i64 = long long;

constexpr int N = 5050, mod = 998244353;
int n;
char s[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 f[N][N];
// 1 -> (
// 2 -> )
void solve() {
  std::cin >> n >> (s + 1);
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(') {
      for (int j = 0; j <= i; j++) {
        f[i][j] = f[i - 1][j];
        if (j) f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
      }
    } else if (s[i] == ')') {
      for (int j = 0; j <= i; j++) {
        f[i][j] = f[i - 1][j];
        if (j != n) f[i][j] = (f[i][j] + f[i - 1][j + 1]) % mod;
      }
    } else {
      for (int j = 0; j <= i; j++) {
        f[i][j] = f[i - 1][j];
        if (j) f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
        if (j != n) f[i][j] = (f[i][j] + f[i - 1][j + 1]) % mod;
      }
    }
  }
  std::cout << f[n][0] << "\n";
}

int main() {
  freopen("bracket.in", "r", stdin);
  freopen("bracket.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
