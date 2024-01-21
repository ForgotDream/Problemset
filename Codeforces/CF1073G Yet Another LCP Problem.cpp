/*
 * @file    CF1073G Yet Another LCP Problem.cpp
 * @author  ForgotDream
 * @brief   Virtual Tree + SAM + DP
 * @date    2024-01-18
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

template <typename T = int>
inline T read() {
  T res;
  std::cin >> res;
  return res;
}

constexpr int N = 4e5 + 50;

int n, m;
char s[N];

int pos[N];

struct SAM {
  int ch[N][26], link[N], len[N], cnt = 1, lst = 1;
  int expand(int d) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1;
    int p = lst;
    for (; p && !ch[p][d]; p = link[p]) ch[p][d] = cur;
    if (!p) {
      link[cur] = 1;
    } else {
      int q = ch[p][d];
      if (len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        int tmp = ++cnt;
        len[tmp] = len[p] + 1, link[tmp] = link[q];
        memcpy(ch[tmp], ch[q], sizeof(ch[q]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }
} sam;

std::vector<int> adj[N];

namespace LCA {

int dfn[N], clk;
int st[20][N];

void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }  
}

inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }

void init() {
  dfs(1, 0);
  for (int i = 1; i <= std::__lg(clk); i++) {
    for (int j = 1; j <= clk - (1 << i) + 1; j++) {
      st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}

inline int queryLCA(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v); 
  int d = std::__lg(v - u++);
  return cmp(st[d][u], st[d][v - (1 << d) + 1]);
}

}  // namespace LCA

using LCA::queryLCA, LCA::dfn;

std::vector<int> vadj[N];
int stk[N], top;
i64 f[N], g[N], ans;

void dp(int u) {
  int hav = f[u], len = sam.len[u];  // hav == 1 means there is a point in u 
  for (auto v : vadj[u]) dp(v), f[u] += f[v], g[u] += g[v];
  for (auto v : vadj[u]) ans += f[v] * (g[u] - g[v]) * len;
  ans += hav * g[u] * len;
}

void solve() {
  std::cin >> n >> m >> (s + 1);
  for (int i = n; i >= 1; i--) pos[i] = sam.expand(s[i] - 'a');

  for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);
  LCA::init();

  for (int k, l, u; m; m--) {
    std::cin >> k >> l;
    
    std::vector<int> t;
    while (k--) t.push_back(pos[u = read()]), f[pos[u]]++;
    while (l--) t.push_back(pos[u = read()]), g[pos[u]]++;

    std::sort(t.begin(), t.end(), [&](int lhs, int rhs) {
      return dfn[lhs] < dfn[rhs];
    });
    t.erase(std::unique(t.begin(), t.end()), t.end());
    u32 siz = t.size();
    for (u32 i = 1; i < siz; i++) t.push_back(queryLCA(t[i - 1], t[i]));
    std::sort(t.begin(), t.end(), [&](int lhs, int rhs) {
      return dfn[lhs] < dfn[rhs];
    });
    t.erase(std::unique(t.begin(), t.end()), t.end());

    stk[top = 1] = t[0];
    for (u32 i = 1; i < t.size(); i++) {
      while (queryLCA(t[i], stk[top]) != stk[top]) top--;
      vadj[stk[top]].push_back(t[i]), stk[++top] = t[i];
    }

    ans = 0, dp(t[0]);
    std::cout << ans << "\n";

    for (auto i : t) vadj[i].clear(), f[i] = g[i] = 0;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
