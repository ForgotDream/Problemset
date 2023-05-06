#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  i64 t1 = 1e18, t2 = 1e18, t3 = 1e18;
  for (int i = 0; i < n; i++) {
    i64 m;
    std::string s;
    std::cin >> m >> s;
    if (s == "10") {
      t1 = std::min(t1, m);
    } else if (s == "01") {
      t2 = std::min(t2, m);
    } else if (s == "11") {
      t3 = std::min(t3, m);
    }
  }

  i64 ans = 2e18;
  if (t1 != 1e18 && t2 != 1e18) {
    ans = std::min(ans, t1 + t2);
  }
  if (t3 != 1e18) {
    ans = std::min(ans, t3);
  }

  if (ans == 2e18) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }

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