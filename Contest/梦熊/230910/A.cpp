/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-09-10
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 1e9 + 7;
std::string s;
int n, d;
namespace N_LESS_THAN_1000 {
int f[N][2], pw[N];
void solve() {
  f[0][0] = 1, pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    f[i][0] = f[i][1] = 0, pw[i] = 10 * pw[i - 1] % d;
    int cur = 0;
    for (int j = i; j; j--) {
      cur = (cur + (s[j] - '0') * pw[i - j]) % d;
      if (!cur) {
        (f[i][0] += f[j - 1][0]) %= mod;
        (f[i][0] += f[j - 1][1]) %= mod;
      } else {
        (f[i][1] += f[j - 1][0]) %= mod;
      }
    }
  }
  std::cout << (f[n][0] + f[n][1]) % mod << "\n";
}
}  // namespace N_LESS_THAN_1000
namespace ND_LESS_THAN_1E6 {
void solve() {
  std::vector f(n + 1, std::vector(d, std::vector<int>(2)));
  f[1][(s[1] - '0') % d] = {1, 0};
  for (int i = 1; i <= n; i++) {
    int cur = (s[i] - '0') % d;
    for (int j = 0; j < d; j++) {
      (f[i][(10 * j + cur) % d][0] += f[i - 1][j][0]) %= mod;
      (f[i][(10 * j + cur) % d][1] += f[i - 1][j][1]) %= mod;
    }
    (f[i][cur][0] += (f[i - 1][0][0] + f[i - 1][0][1]) % mod) %= mod;
    for (int j = 1; j < d; j++) {
      (f[i][cur][1] += f[i - 1][j][0]) %= mod;
    }
  }
  int ans = f[n][0][1];
  for (int i = 0; i < d; i++) (ans += f[n][i][0]) %= mod;
  std::cout << ans << "\n";
}
}  // namespace ND_LESS_THAN_1E6
void solve() {
  std::cin >> s >> d;
  n = s.length(), s = '\0' + s;
  if (n <= 1000) {
    N_LESS_THAN_1000::solve();
  } else if (1ll * n * d <= 1e6) {
    ND_LESS_THAN_1E6::solve();
  }
}

signed main() {
  std::freopen("digit.in", "r", stdin);
  std::freopen("digit.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}