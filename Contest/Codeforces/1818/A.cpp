#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<std::string> v(n);
  int ans = 0;

  for (int i = 0; i < n; i++) {
    bool flg = true;
    std::cin >> v[i];
    for (int j = 0; j < k; j++) {
      if (v[i][j] != v[0][j]) {
        flg = false;
      }
    }
    if (flg) {
      ans++;
    }
  }

  std::cout << ans << "\n";

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