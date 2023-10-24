#include <bits/stdc++.h>
#define int long long

using i64 = long long;

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector<i64> b(n * m);
  for (int i = 0; i < n * m; i++) {
    std::cin >> b[i];
  }

  if (n > m) {
    std::swap(n, m);
  }

  if (n == 1 && m == 1) {
    std::cout << 0 << "\n";
    return;
  } else if (n == 1 || m == 1) {
    int max = *std::max_element(b.begin(), b.end());
    int min = *std::min_element(b.begin(), b.end());
    std::cout << (i64) (n == 1 ? m - 1 : n - 1) * (max - min) << "\n";
    return;
  }

  std::sort(b.begin(), b.end());
  int max = b[n * m - 1], semimax = b[n * m - 2];
  int min = b[0], semimin = b[1];

  int t1 = n * m - 1, t2 = n * m - n, t3 = n * m - m;
  if (t2 < t3) {
    std::swap(t2, t3);
  }

  std::cout << std::max({
    max * t1 - min * t2 - (n - 1) * semimin,
    max * t2 + semimax * (n - 1) - min * t1
  }) << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}