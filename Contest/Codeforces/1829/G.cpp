#include <bits/stdc++.h>

using i64 = long long;

static std::vector<i64> f(1e6 + 1);

void init() {
  f[1] = 1;

  std::vector a(1.5e3, std::vector<i64>(1.5e3));
  std::vector<i64> pre(1e6 + 1);
  int d1 = 1, row = 0;
  for (int i = 1; i <= 1e6; i += d1, d1++, row++) {
    int d2 = 1 + d1, col = 0;
    for (int j = i; j <= 1e6; j += d2, d2++, col++) {
      a[row][col] = j;
      pre[j] = (i64) j * j + (col ? pre[a[row][col - 1]] : 0);
      f[j] = pre[j] + (row ? f[a[row - 1][col]] : 0);
    }
  }

  return;
}

void solve() {
  int n;
  std::cin >> n;
  std::cout << f[n] << "\n";
  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  init();

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}