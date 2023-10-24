#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  i64 d;
  std::cin >> n >> m >> d;

  std::vector<i64> a(n), b(m);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  i64 ans = -1;
  for (int i = 0; i < n; i++) {
    auto it = std::upper_bound(b.begin(), b.end(), a[i] + d);
    if (it == b.begin() || *(--it) < a[i] - d) {
      continue;
    }
    ans = std::max(ans, a[i] + *it);
  }

  std::cout << ans << "\n";

  return 0;
}