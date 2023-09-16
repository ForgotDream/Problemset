/**
 * @file    CF1416C XOR Inverse.cpp
 * @author  ForgotDream
 * @brief   Trie
 * @date    2023-09-08
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e7 + 50, K = 31;
int n, a[N], b[N];
class Trie {
 private:
  int tr[N][2], cnt = 1;
  std::vector<int> a[N];
  i64 f[K][2];
 public:
  void insert(int val, int idx) {
    int p = 1;
    for (int i = 30; ~i; i--) {
      int d = !!(val & (1 << i));
      if (!tr[p][d]) tr[p][d] = ++cnt;
      p = tr[p][d], a[p].push_back(idx);
    }
  }
  void dfs(int u, int idx) {
    // if (!u) return;
    int lc = tr[u][0], rc = tr[u][1];
    if (lc) dfs(lc, idx - 1);
    if (rc) dfs(rc, idx - 1);
    if (!lc && !rc) return;
    int num = 0;
    i64 res = 0;
    for (auto i : a[lc]) {
      while (num < a[rc].size() && a[rc][num] < i) ++num;
      res += num;
    }
    f[idx][0] += res;
    f[idx][1] += 1ll * a[lc].size() * a[rc].size() - res;
  }
  std::pair<i64, i64> solve() {
    dfs(1, 30);
    i64 cnt = 0, res = 0;
    for (int i = 30; ~i; i--) {
      cnt += std::min(f[i][0], f[i][1]);
      if (f[i][1] < f[i][0]) res |= 1 << i;
    }
    return std::pair(cnt, res);
  }
} trie;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], trie.insert(a[i], i);
  auto [cnt, res] = trie.solve();
  std::cout << cnt << " " << res << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}