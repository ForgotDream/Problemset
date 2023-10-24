#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::sort(a.begin(), a.end());

  int ans = 0;
  bool flg = true;
  for (int i = 0; i < n; i++) {
    if (i + 1 <= n - a[i]) {
      ans++;
    } else {
      if (ans <= n - a[i]) {
        flg = false;
        break;
      }
    }
  }

  if (flg) {
    std::cout << n - ans << "\n";
  } else {
    std::cout << -1 << "\n";
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