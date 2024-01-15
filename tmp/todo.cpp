/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-14
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

int n;
std::string s;

int siz[N];

struct GSAM {
  int ch[N][26], link[N], len[N], cnt = 1;
  void insert(std::string_view s) {
    int p = 1;
    for (auto c : s) {
      int d = c - 'a';
      if (!ch[p][d]) ch[p][d] = ++cnt;
      p = ch[p][d];
    }
  }
  int expand(int lst, int d) {
    int cur = ch[lst][d];
    if (len[cur]) return cur;
    len[cur] = len[lst] + 1;
    int p = link[lst];
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
        for (int i = 0; i < 26; i++) ch[tmp][i] = len[ch[q][i]] ? ch[q][i] : 0;
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return cur;
  }
  void build() {
    std::queue<std::pair<int, int>> q;
    for (int i = 0; i < 26; i++) if (ch[1][i]) q.emplace(1, i);
    while (!q.empty()) {
      auto [u, d] = q.front();
      q.pop(), u = expand(u, d);
      for (int i = 0; i < 26; i++) if (ch[u][i]) q.emplace(u, i);
    }
  }
} gsam;

std::vector<int> adj[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> s, gsam.insert(s);
  }
  gsam.build();

  for (int i = 2; i <= gsam.cnt; i++) adj[gsam.link[i]].push_back(i);
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
