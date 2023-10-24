#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<std::pair<i64, i64>> a(n);
  std::vector<std::unordered_map<i64, i64>> mp(n + 1);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first;
  }
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].second;
    mp[a[i].first][a[i].second]++;
  }

  std::sort(a.begin(), a.end());

  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    i64 tmp = 0;
    for (auto j : mp[i]) {
      i64 p = i * i - j.first;
      if (p == j.first) {
        tmp += mp[i][p] * (mp[i][p] - 1);
      } else {
        if (mp[i].count(p)) {
          tmp += mp[i][p] * j.second;
        }
      }
    }
    ans += tmp >> 1;
  }

  int sqr = std::ceil(std::sqrt(n));
  for (int i = 1; i <= sqr; i++) {
    if (mp[i].empty()) {
      continue;
    }
    int j = std::lower_bound(
      a.begin(), a.end(), std::make_pair(1ll * i, LONG_LONG_MAX)
    ) - a.begin();
    for (; j < n; j++) {
      if (a[j].first * i > 2 * n) {
        continue;
      }
      i64 p = a[j].first * i - a[j].second;
      if (mp[i].count(p)) {
        ans += mp[i][p];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (a[i].first <= sqr) {
      continue;
    }
    for (int j = a[i].first + 1; j <= n && a[i].first * j <= 2 * n; j++) {
      for (auto k : mp[j]) {
        if (k.first + a[i].second == a[i].first * j) {
          ans += k.second;
        }
      }
    }
  }

  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}