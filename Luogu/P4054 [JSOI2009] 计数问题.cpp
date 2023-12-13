/**
 * @file    P4054 [JSOI2009] 计数问题.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-12-12
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 350, M = 105;
int n, m, a[N][N], q;
struct BIT {
  int tree[N][N];
  void modify(int u, int v, int val) {
    for (int i = u; i <= n; i += i & -i) {
      for (int j = v; j <= m; j += j & -j) tree[i][j] += val;
    }
  }
  int query(int u, int v) {
    int res = 0;
    for (int i = u; i; i -= i &-i) {
      for (int j = v; j; j -= j & -j) res += tree[i][j];
    }
    return res;
  }
} bit[M];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j], bit[a[i][j]].modify(i, j, 1);
  std::cin >> q;
  for (int opt, x1, y1, x2, y2, c; q; q--) {
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> x1 >> y1 >> c;
      bit[a[x1][y1]].modify(x1, y1, -1);
      a[x1][y1] = c;
      bit[a[x1][y1]].modify(x1, y1, 1);
    } else {
      std::cin >> x1 >> x2 >> y1 >> y2 >> c;
      int res = bit[c].query(x2, y2);
      res -= bit[c].query(x1 - 1, y2);
      res -= bit[c].query(x2, y1 - 1);
      res += bit[c].query(x1 - 1, y1 - 1);
      std::cout << res << "\n";
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
