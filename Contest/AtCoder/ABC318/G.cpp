#include <iostream>
#include <stack>
#include <vector>

using i64 = long long;

constexpr int N = 6e5 + 50;
int n, m;
int a, b, c;
std::vector<int> adj[N], g[N];
int dfn[N], clk, low[N];
bool val[N];
int cnt;
std::stack<int> s;
void tarjan(int u) {
  low[u] = dfn[u] = ++clk;
  s.push(u);
  for (auto v : adj[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = std::min(low[u], low[v]);
      if (low[v] == dfn[u]) {
        ++cnt;
        int p;
        do {
          p = s.top(), s.pop();
          g[cnt].push_back(p), g[p].push_back(cnt);
          val[cnt] |= (p == b);
        } while (p != v);
        g[cnt].push_back(u), g[u].push_back(cnt);
        val[cnt] |= (u == b);
      }
    } else {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
}
int dep[N], fa[N];
void dfs(int u, int frm) {
  dep[u] = dep[frm] + 1, fa[u] = frm;
  for (auto v : g[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
void solve() {
  std::cin >> n >> m;
  std::cin >> a >> b >> c;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  cnt = n;
  tarjan(1);
  dfs(1, 0);
  bool ans = val[a] | val[c];
  while (a != c) {
    if (dep[a] < dep[c]) std::swap(a, c);
    a = fa[a], ans |= val[a];
  }
  if (ans) std::cout << "Yes\n";
  else std::cout << "No\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}