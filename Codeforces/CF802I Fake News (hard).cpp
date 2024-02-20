/*
 * @file    CF802I Fake News (hard).cpp
 * @author  ForgotDream
 * @brief   SAM
 * @date    2024-02-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

struct SAM {
  int ch[N][26], len[N], link[N], lst = 1, cnt = 1;

  void clear() {
    memset(ch + 1, 0, sizeof(int[26]) * cnt);
    memset(len + 1, 0, sizeof(int) * cnt);
    memset(link + 1, 0, sizeof(int) * cnt);
    lst = cnt = 1;
  }

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
        memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }
} sam;

std::string s;

std::vector<int> adj[N];
i64 siz[N], ans;

void dfs(int u) {
  for (auto v : adj[u]) dfs(v), siz[u] += siz[v];
  ans += siz[u] * siz[u] * (sam.len[u] - sam.len[sam.link[u]]);
}

void solve() {
  for (int i = 1; i <= sam.cnt; i++) adj[i].clear(), siz[i] = 0;
  sam.clear(), ans = 0;

  std::cin >> s;
  for (auto c : s) siz[sam.expand(c - 'a')]++;
  for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);

  dfs(1), std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
