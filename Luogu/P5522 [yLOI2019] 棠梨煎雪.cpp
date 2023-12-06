/**
 * @file    P5522 [yLOI2019] 棠梨煎雪.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-12-03
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e5 + 50, M = 35;
int n, m, q;
char s[N][M], t[M];
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= m; i += i & -i) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
  int query(int l, int r) { return query(r) - query(l - 1); }
} bit[M * 3];
void solve() {
  std::cin >> n >> m >> q;
  for (int i = 1; i <= m; i++) {
    std::cin >> s[i];
    for (int j = 0; j < n; j++) {
      if (s[i][j] != '?') bit[2 * j + s[i][j] - '0'].modify(i, 1);
    }
  }
  // std::cerr << "waht\n";
  int ans = 0;
  for (int opt, l, r, pos; q; q--) {
    std::cin >> opt;
    if (opt == 0) {
      std::cin >> l >> r;
      int cur = 1;
      for (int j = 0; j < n; j++) {
        int cnt[2], tmp;
        for (int k = 0; k < 2; k++) cnt[k] = bit[2 * j + k].query(l, r);
        if (cnt[0] && cnt[1]) tmp = 0;
        else if (cnt[0] || cnt[1]) tmp = 1;
        else tmp = 2;
        cur *= tmp;
        if (!cur) break;
      }
      ans ^= cur;
    } else {
      std::cin >> pos >> t;
      for (int j = 0; j < n; j++) {
        if (s[pos][j] != '?') bit[2 * j + s[pos][j] - '0'].modify(pos, -1);
      }
      strcpy(s[pos], t);
      for (int j = 0; j < n; j++) {
        if (s[pos][j] != '?') bit[2 * j + s[pos][j] - '0'].modify(pos, 1);
      }
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
