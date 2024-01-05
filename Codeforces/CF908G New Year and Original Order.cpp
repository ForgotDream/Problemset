/*
 * @file    CF908G New Year and Original Order.cpp
 * @author  ForgotDream
 * @brief   Digital DP
 * @date    2024-01-04
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 705, mod = 1e9 + 7;
int n;
std::string s;

int f[N][N][10];
int dfs(int pos, int sum, int dn, bool lim) {
  if (!pos) return !sum;
  if (!lim && ~f[pos][sum][dn]) return f[pos][sum][dn];

  int res = 0, up = lim ? s[pos] - '0' : 9;
  for (int i = 0; i <= up; i++) {
    res = (res + dfs(pos - 1, sum - (i >= dn), dn, lim && i == up)) % mod;
  }

  if (!lim) f[pos][sum][dn] = res;
  return res;
}

void solve() {
  std::cin >> s, n = s.length();

  std::reverse(s.begin(), s.end());
  s = ' ' + s;

  memset(f, -1, sizeof(f));
  int ans = 0;
  for (int i = 1; i <= 9; i++) {
    for (int j = 1, cur = 1; j <= n; j++, cur = (10ll * cur + 1) % mod) {
      ans = (ans + 1ll * dfs(n, j, i, true) * cur % mod) % mod;
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
