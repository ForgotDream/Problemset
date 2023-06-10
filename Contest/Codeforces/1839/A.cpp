#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, k;
  std::cin >> n >> k;

  if (n == 1) {
    std::cout << 1 << "\n";
    return;
  } else if (k == 1) {
    std::cout << n << "\n";
    return;
  }

  std::vector<int> a(n);
  int cnt = 0;
  bool flg = false;
  for (int i = 0; i < (n + 1) / 2; i++) {
    if (std::ceil(1. * (i + 1) / k) != std::ceil(1. * i / k)) {
      cnt++;
      if ((n & 1) && i == (n + 1) / 2 - 1) {
        flg = true;
      }
    }
  }

  std::cout << 2 * cnt - flg << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}