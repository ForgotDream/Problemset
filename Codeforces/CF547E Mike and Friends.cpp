/*
 * @file    CF547E Mike and Friends.cpp
 * @author  ForgotDream
 * @brief   ACAM
 * @date    2024-01-18
 */
#include <bits/stdc++.h>

using i64 = long long;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 5e5 + 50;

int n, m;
std::string s[N];

int fa[N];

struct ACAM {
  int ch[N][26], nxt[N], cnt;
  int insert(std::string_view s) {
    int p = 0;
    for (auto c : s) {
      int d = c - 'a';
      if (!ch[p][d]) ch[p][d] = ++cnt, fa[ch[p][d]] = p;
      p = ch[p][d];
    }
    return p;
  }
  void build() {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) if (ch[0][i]) q.push(ch[0][i]);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < 26; i++) {
        int &v = ch[u][i];
        if (!v) v = ch[nxt[u]][i];
        else nxt[v] = ch[nxt[u]][i], q.push(v);
      }
    }
  }
} ac;

std::vector<int> adj[N];
int pos[N];

int dfn[N], siz[N], clk;
void dfs(int u) {
  dfn[u] = ++clk, siz[u] = 1;
  for (auto v : adj[u]) dfs(v), siz[u] += siz[v];
}
inline int in(int u) { return dfn[u]; }
inline int out(int u) { return dfn[u] + siz[u] - 1; }

std::vector<ti3> qry[N];

struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= ac.cnt + 1; i += i & -i) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
  int query(int l, int r) { return query(r) - query(l - 1); }
} bit;

int ans[N];

void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> s[i], pos[i] = ac.insert(s[i]);
  ac.build();

  for (int i = 1; i <= ac.cnt; i++) adj[ac.nxt[i]].push_back(i);
  dfs(0);

  for (int i = 1, l, r, k; i <= m; i++) {
    std::cin >> l >> r >> k;
    qry[l - 1].emplace_back(k, i, -1), qry[r].emplace_back(k, i, 1);
  }

  for (int i = 1; i <= n; i++) {
    for (int p = pos[i]; p; p = fa[p]) bit.modify(dfn[p], 1);
    for (auto [k, id, d] : qry[i]) {
      ans[id] += d * bit.query(in(pos[k]), out(pos[k]));
    }
  }

  for (int i = 1; i <= m; i++) std::cout << ans[i] << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
