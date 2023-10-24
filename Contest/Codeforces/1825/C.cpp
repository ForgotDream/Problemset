#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> x(n), a;
  int lcnt = 0, rcnt = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
    if (x[i] > 0) {
      a.push_back(x[i]);
    } else if (x[i] == -1) {
      lcnt++;
    } else if (x[i] == -2) {
      rcnt++;
    }
  }

  if (a.empty()) {
    std::cout << std::min(m, std::max(lcnt, rcnt)) << "\n";
    return;
  }

  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());
  n = a.size();

  std::vector<int> l(n), r(n);
  int max = std::min(m - n, std::max(lcnt, rcnt));
  for (int i = 0; i < n; i++) {
    l[i] = a[i] - i - 1;
    r[i] = m - a[i] - (n - i - 1);
    max = std::max(max, std::min(lcnt, l[i]) + std::min(rcnt, r[i]));
  }

  int ans = n + max;
  std::cout << ans << "\n";

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