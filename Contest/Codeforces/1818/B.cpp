#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  if (n % 2 == 1 && n != 1) {
    std::cout << -1 << "\n";
    return;
  } else if (n == 1) {
    std::cout << 1 << "\n";
    return;
  }

  int cur = n - 1;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) {
      std::cout << cur << " "; 
    } else {
      std::cout << cur + 1 << " ";
      cur -= 2;
    }
  }
  std::cout << "\n";

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