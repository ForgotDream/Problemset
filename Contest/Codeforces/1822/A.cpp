#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, t;
  std::cin >> n >> t;

  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }

  int ans = -1, pivot = -1;
  for (int i = 0; i < n; i++) {
    if (a[i] + i <= t && ans < b[i]) {
      ans = b[i];
      pivot = i + 1;
    }
  }

  std::cout << pivot << "\n";

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