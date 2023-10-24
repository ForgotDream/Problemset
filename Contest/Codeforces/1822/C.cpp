#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  i64 n;
  std::cin >> n;

  i64 ans = 0;
  if (n & 1) {
    ans += (n + 1) * (n + 1) / 2;
    ans += n + 1 + (2 + n - 1) * (n / 2);
  } else {
    ans += (2 + n) * (n / 2);
    ans += n + 1 + (1 + n - 1) * (n / 2);
  }

  std::cout << ans + 1 << "\n";

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}