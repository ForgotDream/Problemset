#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n), b(m);
  int max = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    max = std::max(max, a[i]);
  }
  for (int i = 0; i < m; i++) {
    std::cin >> b[i];
    max = std::max(max, b[i]);
  }

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  auto check = [&](int num) {
    int c1 = std::upper_bound(a.begin(), a.end(), num) - a.begin();
    int c2 = b.end() - std::lower_bound(b.begin(), b.end(), num);
    return c1 >= c2;
  };

  int lo = 1, hi = max + 1, ans = -1;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) {
      hi = mid - 1, ans = mid;
    } else {
      lo = mid + 1;
    }
  }
  std::cout << ans << "\n";

  return 0;
}