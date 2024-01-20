/*
 * @file    P1117 [NOI2016] 优秀的拆分.cpp
 * @author  ForgotDream
 * @brief   SAM
 * @date    2024-01-17
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;

int n;
std::string s;

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
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }
};

struct Solver {
  SAM sam;
  std::vector<int> adj[N];
  int pos[N];

  int st[20][N], dfn[N], clk;
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
    // std::cerr << cmp(st[d][u], st[d][v - (1 << d) + 1]) << " ";
    return cmp(st[d][u], st[d][v - (1 << d) + 1]);
  }

  void work() { 
    for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);
    dfs(1, 0), init(); 
  }
  int calc(int l, int r) { return sam.len[getLCA(pos[l], pos[r])]; }

  void clear() {
    for (int i = 1; i <= sam.cnt; i++) adj[i].clear();
    sam = SAM(), memset(pos, 0, sizeof(pos)), clk = 0;
  }
} cis, trans;

i64 f[N], g[N];

void clear() {
  memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
  cis.clear(), trans.clear();
}

void solve() {
  clear();

  std::cin >> s, n = s.length(), s = " " + s;
  for (int i = 1; i <= n; i++) cis.pos[i] = cis.sam.expand(s[i]);
  for (int i = n; i >= 1; i--) trans.pos[i] = trans.sam.expand(s[i]);

  cis.work(), trans.work();

  for (int len = 1; len <= n / 2; len++) {
    for (int i = len; i + len - 1 <= n; i += len) {
      int l = i, r = i + len, lcp = 0, lcs = 0;
      if (l > 1) lcp = std::min(cis.calc(l - 1, r - 1), len - 1);
      if (r <= n) lcs = std::min(trans.calc(l, r), len);
      // std::cerr << l << " " << r << " " << lcp << " " << lcs << "\n";
      if (lcp + lcs >= len) {
        f[r + lcs]--, f[r + lcs - 1 - (lcp + lcs - len)]++;
        g[l - lcp]++, g[l - lcp + 1 + (lcp + lcs - len)]--;
      }
    }
  }

  for (int i = 1; i <= n; i++) f[i] += f[i - 1], g[i] += g[i - 1];
  i64 ans = 0;
  for (int i = 1; i < n; i++) ans += f[i] * g[i + 1];
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();
  
  return 0;
}
