#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n;
i64 a[N], p;

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
