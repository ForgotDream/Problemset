/*
 * @file    P3181 [HAOI2016] 找相同字符.cpp
 * @author  ForgotDream
 * @brief   SAM
 * @date    2024-01-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 4e5 + 50;

std::string s, t;

struct SAM {
  int ch[N][26], len[N], link[N], siz[N], lst = 1, cnt = 1;

  int expand(int d) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1, siz[cur] = 1;
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

  void dfs1(int u) {
    for (auto v : adj[u]) dfs1(v), siz[u] += siz[v];
    sum[u] = 1ll * siz[u] * (len[u] - len[link[u]]);
  }
  void dfs2(int u) {
    for (auto v : adj[u]) sum[v] += sum[u], dfs2(v);
  }

  void init() {
    for (int i = 2; i <= cnt; i++) adj[link[i]].push_back(i);
    dfs1(1), dfs2(1);
    // for (int i = 1; i <= cnt; i++) std::cerr << siz[i] << " " << sum[i] << "\n";
  }

  i64 calc(std::string_view s) {
    int p = 1, cur = 0;
    i64 res = 0;
    for (auto c : s) {
      int d = c - 'a';
      while (p != 1 && !ch[p][d]) p = link[p], cur = len[p];
      if (ch[p][d]) {
        p = ch[p][d], cur = std::min(cur + 1, len[p]);
        // res += sum[p] - siz[p] * (cur - len[link[p]]);
        res += sum[p] - 1ll * siz[p] * (len[p] - cur);
        // std::cerr << p << " " << sum[p] << " " << siz[p] << " " << len[p] << " " << cur << "\n";
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
