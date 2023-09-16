/**
 * @file    CF467D Fedor and Essay.cpp
 * @author  ForgotDream
 * @brief   Tarjan
 * @date    2023-09-05
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include <map>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m;
std::string s[N];
int cnt, a[N], len[N];
std::map<std::string, int> mp;
std::vector<int> adj[N], g[N];
std::string tolower(const std::string &s) {
  auto res = s;
  for (auto &c : res) c = std::tolower(c);
  return res;
}
int init(const std::string &s) {
  if (mp.count(s)) return mp[s];
  mp[s] = ++cnt;
  a[cnt] = std::count(s.begin(), s.end(), 'r'), len[cnt] = s.length();
  return cnt;
}
int deg[N];
namespace SCC {
std::stack<int> s;
int dfn[N], low[N], clk;
bool ins[N];
int cnt, bln[N], len[N], f[N];
void tarjan(int u) {
  dfn[u] = low[u] = ++clk;
  s.push(u), ins[u] = true;
  for (auto v : adj[u]) {
    if (!dfn[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
    else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    ++cnt;
    len[cnt] = f[cnt] = 1e9;
    int p;
    do {
      p = s.top(), s.pop();
      bln[p] = cnt, ins[p] = false;
      if (a[p] < f[cnt]) f[cnt] = a[p], len[cnt] = ::len[p];
      else if (a[p] == f[cnt]) len[cnt] = std::min(len[cnt], ::len[p]);
    } while (p != u);
  }
}
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> s[i], s[i] = tolower(s[i]), init(s[i]);
  }
  std::cin >> m;
  for (int i = 1; i <= m; i++) {
    std::string s, t;
    std::cin >> s >> t;
    s = tolower(s), t = tolower(t);
    int u = init(s), v = init(t);
    adj[v].push_back(u);
  }
  using SCC::dfn, SCC::tarjan, SCC::bln;
  for (int i = 1; i <= cnt; i++) {
    if (!dfn[i]) tarjan(i);
  }
  for (int u = 1; u <= cnt; u++) {
    for (auto v : adj[u]) {
      if (bln[u] != bln[v]) g[bln[u]].push_back(bln[v]);
    }
  }
  for (int i = 1; i <= SCC::cnt; i++) {
    std::sort(g[i].begin(), g[i].end());
    g[i].erase(std::unique(g[i].begin(), g[i].end()), g[i].end());
    for (auto v : g[i]) ++deg[v];
  }
  std::queue<int> q;
  for (int i = 1; i <= SCC::cnt; i++) {
    if (!deg[i]) q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (SCC::f[v] > SCC::f[u]) {
        SCC::f[v] = SCC::f[u], SCC::len[v] = SCC::len[u];
      } else if (SCC::f[v] == SCC::f[u]) {
        SCC::len[v] = std::min(SCC::len[v], SCC::len[u]);
      }
      if (!--deg[v]) q.push(v);
    }
  }
  i64 ans = 0, len = 0;
  for (int i = 1; i <= n; i++) {
    ans += SCC::f[bln[mp[s[i]]]], len += SCC::len[bln[mp[s[i]]]];
  }
  std::cout << ans << " " << len << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}