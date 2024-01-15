/*
 * @file    P6139 【模板】广义后缀自动机（广义 SAM）.cpp
 * @author  ForgotDream
 * @brief   GSAM
 * @date    2024-01-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e6 + 50;

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
        link[tmp] = link[q], len[tmp] = len[p] + 1;
        for (int i = 0; i < 26; i++) ch[tmp][i] = len[ch[q][i]] ? ch[q][i] : 0;
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return cur;
  }
  void build() {
    std::queue<pii> q;
    for (int i = 0; i < 26; i++) if (ch[1][i]) q.emplace(1, i);
    while (!q.empty()) {
      auto [u, d] = q.front();
      // std::cerr << u << " " << d << "\n";
      q.pop(), u = expand(u, d);
      for (int i = 0; i < 26; i++) if (ch[u][i]) q.emplace(u, i);
    }
  }
} gsam;

int n;
std::string s;

void solve() {
  std::cin >> n;
  while (n--) std::cin >> s, gsam.insert(s);
  gsam.build();

  i64 ans = 0;
  for (int i = 1; i <= gsam.cnt; i++) ans += gsam.len[i] - gsam.len[gsam.link[i]];
  // for (int i = 1; i <= gsam.cnt; i++) std::cerr << gsam.link[i] << "\n";
  std::cout << ans << "\n" << gsam.cnt << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
