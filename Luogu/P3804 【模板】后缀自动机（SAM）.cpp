/*
 * @file    P3804 【模板】后缀自动机（SAM）.cpp
 * @author  ForgotDream
 * @brief   SAM
 * @date    2024-01-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 50;

std::string s;

std::vector<int> adj[N];
int siz[N];
i64 ans;

struct SAM {
  int ch[N][26], link[N], len[N], cnt, lst;
  void init() {
    link[0] = -1, len[0] = 0, cnt = 0, lst = 0;
  }
  void expand(char c) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1, siz[cur] = 1;
    int p = lst;
    for (; ~p && !ch[p][c - 'a']; p = link[p]) ch[p][c - 'a'] = cur;
    if (p == -1) return link[cur] = 0, lst = cur, void();
    int q = ch[p][c - 'a'];
    if (len[p] + 1 == len[q]) {
      link[cur] = q;
    } else {
      int tmp = ++cnt;
      len[tmp] = len[p] + 1, link[tmp] = link[q];
      memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
      for (; ~p && ch[p][c - 'a'] == q; p = link[p]) ch[p][c - 'a'] = tmp;
      link[q] = link[cur] = tmp;
    }
    lst = cur;
  }
  void build(const std::string_view &s) {
    init();
    for (auto c : s) expand(c);
  }
} sam;

void dfs(int u) {
  for (auto v : adj[u]) dfs(v), siz[u] += siz[v];
  if (siz[u] != 1) ans = std::max(ans, 1ll * siz[u] * sam.len[u]);
}

void solve() {
  std::cin >> s, sam.build(s);
  for (int i = 1; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);
  dfs(0), std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
