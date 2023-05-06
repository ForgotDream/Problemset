#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  int ans = 0, cnt = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] == 1) {
      ans = std::max(ans, cnt);
      cnt = 0;
    } else {
      cnt++;
    }
  }

  if (cnt) {
    ans = std::max(ans, cnt);
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