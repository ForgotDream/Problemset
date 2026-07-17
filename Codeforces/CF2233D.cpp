/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) std::cin >> a[i];

  if (n <= 3) {
    std::cout << "YES\n";
    return;
  }

  int d = 0;
  for (int i = 1; i < n; i++) if (a[i] != a[i - 1]) d++;

  auto b = a;
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  int c = b.size();

  auto idx = [&](int col) {
    return std::lower_bound(b.begin(), b.end(), col) - b.begin();
  };

  if (d == c - 1) {
    std::cout << "YES\n";
    return;
  } else if (d > c - 1 + 4) {
    std::cout << "NO\n";
    return;
  }

  std::vector<std::array<int, 3>> blk;
  for (int i = 0, len = 0; i < n; i = i + len) {
    len = 0;
    while (i + len < n && a[i] == a[i + len]) len++;
    blk.push_back({a[i], i, i + len - 1});
  }

  std::vector<int> blk_cnt(c);
  for (auto [col, l, r] : blk) blk_cnt[idx(col)]++;

  std::vector<int> cands;
  for (auto [col, l, r] : blk) {
    if (blk_cnt[idx(col)] >= 2) {
      cands.push_back(l), cands.push_back(r);
      if (l > 0) cands.push_back(l - 1);
      if (r < n - 1) cands.push_back(r + 1);
    }
  }

  std::sort(cands.begin(), cands.end());
  cands.erase(std::unique(cands.begin(), cands.end()), cands.end());

  int m = cands.size();
  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m; j++) {
      int u = cands[i], v = cands[j];
      if (a[u] == a[v]) continue;

      std::vector<int> changed;
      for (auto k : {u - 1, u, v - 1, v}) {
        if (k >= 0 && k < n - 1) changed.push_back(k);
      }

      std::sort(changed.begin(), changed.end());
      changed.erase(std::unique(changed.begin(), changed.end()), changed.end());

      int cur = 0;
      for (auto k : changed) if (a[k] != a[k + 1]) cur++;

      std::swap(a[u], a[v]);

      int nxt = 0;
      for (auto k : changed) if (a[k] != a[k + 1]) nxt++;

      if (d - cur + nxt == c - 1) {
        std::cout << "YES\n";
        return;
      }

      std::swap(a[u], a[v]);
    }
  }

  std::cout << "NO\n";
}

// 1 2 1 2 1
// [1 1] .. [1 1] 
// i|i+1 i-1|i j|j+1 j-1|j

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
