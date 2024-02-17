#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

i64 n, f[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> f[i];
  for (i64 i = 1, s, t; i < n; i++) {
    std::cin >> s >> t;
    f[i + 1] += f[i] / s * t;
  }
  std::cout << f[n] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
