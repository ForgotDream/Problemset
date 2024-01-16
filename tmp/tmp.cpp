/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50;

int n, m, k;
char s[N];

struct SAM {
  int ch[N][26], len[N], link[N], cnt = 1, lst = 1;
  int expand(char c) {
    int cur = ++cnt, d = c - 'a';
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
        memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
        for (; p && ch[p][d] == q; q = link[q]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }
} sam;

int pos[N];
std::vector<int> adj[N];

int st[21][N], dfn[N], clk;
inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  for (auto v : adj[u]) dfs(v, u);
}
void init() {
  for (int i = 1; i <= std::__lg(sam.cnt); i++) {
    for (int j = 1; j <= sam.cnt - (1 << i) + 1; j++) {
      st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}
inline int getLCA(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return cmp(st[d][u], st[d][v - (1 << d) + 1]);
}

void solve() {
  std::cin >> n >> m >> k >> (s + 1);

  for (int i = 1; i <= n; i++) pos[i] = sam.expand(s[i]);
  for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);
  
  for (int l, r, i = 1; i <= m; i++) {
    std::cin >> l >> r;
  }
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
