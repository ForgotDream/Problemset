/**
 * @file    P8511 [Ynoi Easy Round 2021] TEST_68.cpp
 * @author  ForgotDream
 * @brief   Trie + DFS
 * @date    2023-11-02
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;
using pli = std::pair<i64, int>;

constexpr int N = 5e5 + 50;
int n, fa[N];
i64 a[N], ans[N];
std::vector<int> adj[N];
int p[N], cnt;
bool vis[N];
struct Trie {
  int tr[60 * N][2], idx[60 * N], cnt;
  void clear() { memset(tr, 0, sizeof(tr)), memset(idx, 0, sizeof(idx)), cnt = 0; }
  void insert(i64 num, int id) {
    int p = 0;
    for (int i = 59; ~i; i--) {
      int d = !!(num & (1ll << i));
      if (!tr[p][d]) tr[p][d] = ++cnt;
      p = tr[p][d];
    }
    idx[p] = id;
  }
  pli query(i64 num) {
    i64 res = 0;
    int p = 0;
    for (int i = 59; ~i; i--) {
      int d = !(num & (1ll << i));
      if (tr[p][d]) p = tr[p][d], res += 1ll << i;
      else p = tr[p][!d];
    }
    return {res, idx[p]};
  }
} trie;
i64 dfs2(int u) {
  trie.insert(a[u], u);
  i64 res = 0;
  for (auto v : adj[u]) res = std::max(dfs2(v), res);
  res = std::max(res, trie.query(a[u]).first);
  return res;
}
void dfs1(int u) {
  trie.insert(a[u], u), ans[u] = std::max(ans[u], 0ll);
  i64 res = std::max(ans[u], trie.query(a[u]).first);
  for (auto v : adj[u]) {
    if (vis[v]) continue;
    res = std::max(res, dfs2(v));
  }
  for (auto v : adj[u]) {
    if (!vis[v]) continue;
    ans[v] = res, dfs1(v);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 2; i <= n; i++) std::cin >> fa[i], adj[fa[i]].push_back(i);
  for (int i = 1; i <= n; i++) std::cin >> a[i], trie.insert(a[i], i);
  i64 mx = -1e18, x = 0, y = 0;
  for (int i = 1; i <= n; i++) {
    auto [val, j] = trie.query(a[i]);
    if (val > mx) x = i, y = j, mx = val;
  }
  memset(ans, -1, sizeof(ans));
  trie.clear();
  for (int u = x; u; u = fa[u]) vis[u] = true;
  dfs1(1);
  for (int u = x; u; u = fa[u]) vis[u] = false;
  trie.clear();
  for (int u = y; u; u = fa[u]) vis[u] = true;
  dfs1(1);
  for (int i = 1; i <= n; i++) {
    if (ans[i] == -1) std::cout << mx << "\n";
    else std::cout << ans[i] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
