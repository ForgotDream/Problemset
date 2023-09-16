#include <iostream>
#include <stack>
#include <unordered_set>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 20;
int n, v[N], w[N], m;
int p[M], cnt;
i64 ans;
struct BIT {
  int n;
  i64 tree[N];
  std::unordered_set<int> s;
  void clear() {
    for (const auto &i : s) tree[i] = 0;
    s.clear();
  }
  void modify(int u, i64 val) {
    if (!u) return;
    for (int i = u; i <= n; i += (i & -i)) {
      tree[i] = std::max(tree[i], val), s.insert(i);
    }
  }
  i64 query(int u) {
    i64 res = 0;
    for (int i = u; i; i -= (i & -i)) res = std::max(res, tree[i]);
    return res;
  }
} bit;
void dfs1(int u, int lim, i64 v = 0, int w = 0) {
  if (w > lim) return;
  if (u == cnt / 2 + 1) return ans = std::max(ans, v), bit.modify(w, v);
  dfs1(u + 1, lim, v, w);
  dfs1(u + 1, lim, v + ::v[p[u]], w + ::w[p[u]]);
}
void dfs2(int u, int lim, i64 v = 0, int w = 0) {
  if (w > lim) return;
  if (u == cnt + 1) return void(ans = std::max(bit.query(lim - w) + v, ans));
  dfs2(u + 1, lim, v, w);
  dfs2(u + 1, lim, v + ::v[p[u]], w + ::w[p[u]]);
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> v[i] >> w[i];
  std::cin >> m;
  for (int i = 1, u, l; i <= m; i++) {
    std::cin >> u >> l;
    bit.clear(), bit.n = l;
    ans = cnt = 0;
    while (u) p[++cnt] = u, u >>= 1;
    dfs1(1, l), dfs2(cnt / 2 + 1, l);
    std::cout << ans << "\n";
  }
}

int main() {
  std::freopen("knapsack.in", "r", stdin);
  std::freopen("knapsack.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}