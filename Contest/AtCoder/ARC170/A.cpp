#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

int n;
std::string s, t;

int f[N], g[N];

void solve() {
  std::cin >> n >> s >> t;

  for (int i = 0; i < n; i++) {
    if (i) f[i] = f[i - 1];
    if (s[i] == t[i] && s[i] == 'A') f[i]++;
    if (s[i] != t[i] && s[i] == 'B') f[i]++;
  }
  for (int i = n - 1; i >= 0; i--) {
    if (i != n - 1) g[i] = g[i + 1];
    if (s[i] == t[i] && s[i] == 'B') g[i]++;
    if (s[i] != t[i] && s[i] == 'A') g[i]++;
  }

  int ans = 0, p = 0, k = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == t[i]) continue;

    if (s[i] == 'B') {
      if (!g[i]) return std::cout << -1 << "\n", void();
      p++, ans++;
    } else {
      if (!f[i]) return std::cout << -1 << "\n", void();
      ans++;
      if (p) ans--, p--;
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
