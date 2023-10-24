#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, x;
  std::cin >> n >> x;

  std::vector a(3, std::vector<int>(n));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
    }
  }

  if (!x) {
    std::cout << "Yes\n";
    return;
  }

  auto check = [&](int u, int v) {
    for (int i = 0; i <= 30; i++) {
      if ((u & (1 << i)) && !(v & (1 << i))) {
        return false;
      }
    }
    return true;
  };

  std::array<int, 3> f { 0, 0, 0 };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n; j++) {
      if (!check(f[i] | a[i][j], x)) {
        break;
      }
      f[i] |= a[i][j];
    }
  }

  if ((f[0] | f[1] | f[2]) != x) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
  }
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