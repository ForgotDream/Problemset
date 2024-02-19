#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e6 + 50;

int n;
char s[N];

i64 f[N];

void solve() {
  std::cin >> n >> (s + 1);
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '1') f[i] = f[std::max(0, i - 3)] + i;
    else f[i] = f[i - 1];
    ans += f[i];
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
