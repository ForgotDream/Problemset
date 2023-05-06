#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> deg(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    deg[u]++, deg[v]++;
  }

  std::sort(deg.begin(), deg.end());

  int pivot = 0;
  while (pivot < n && deg[pivot] == 1) {
    pivot++;
  }

  std::vector<std::pair<int, int>> cnt;
  for (; pivot < n; pivot++) {
    if (deg[pivot] != deg[pivot - 1]) {
      cnt.emplace_back(deg[pivot], 1);
    } else {
      cnt[cnt.size() - 1].second++;
    }
  }

  if (cnt.size() == 1) {
    std::cout << cnt[0].first << " " << cnt[0].first - 1 << "\n";
  } else {
    if (cnt[0].second > cnt[1].second) {
      std::swap(cnt[0], cnt[1]);
    }
    std::cout << cnt[0].first << " " << cnt[1].first - 1 << "\n";
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