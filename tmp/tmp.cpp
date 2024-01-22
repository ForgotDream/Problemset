/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-21
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

std::string s, t;

struct SAM {
  int ch[N][26], len[N], link[N], siz[N], lst = 1, cnt = 1;

  int expand(int d) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1, siz[cur]++;
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

  std::vector<int> adj[N];
  i64 sum[N];

  void dfs(int u) {
    for (auto v : adj[u]) dfs(v), siz[u] += siz[v], sum[u] += sum[v];
    sum[u] += 1ll * len[u] * siz[u];
  }

  void init() {
    for (int i = 2; i <= cnt; i++) adj[link[i]].push_back(i);
    dfs(1);
  }

  i64 calc(std::string_view s) {
    int p = 1, cur = 0, res = 0;
    for (auto c : s) {
      int d = c - 'a';
      while (p != 1 && !ch[p][d]) p = link[p], cur = len[p];
      if (ch[p][d]) {
        p = ch[p][d], cur = std::min(cur + 1, len[p]);
        res += sum[p] - siz[p] * (len[p] - cur);
      }
    }
    return res;
  }
} sam;

void solve() {
  std::cin >> s >> t;
  for (auto c : s) sam.expand(c - 'a');
  sam.init();
  std::cout << sam.calc(t) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
