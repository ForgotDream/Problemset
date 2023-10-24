#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  if (n == 3) {
    std::cout << -1 << "\n";
  } else if (n == 1) {
    std::cout << 1 << "\n";
  } else {
    int d = n;
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
      sum += d;
      d--;
      std::cout << sum % n << " \n"[i == n - 1];
    }
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