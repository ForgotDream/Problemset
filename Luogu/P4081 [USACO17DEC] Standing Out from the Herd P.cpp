/*
 * @file    P4081 [USACO17DEC] Standing Out from the Herd P.cpp
 * @author  ForgotDream
 * @brief   GSAM
 * @date    2024-01-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e5 + 50;

int n;
std::string s[N];

struct GSAM {
  int ch[N][26], len[N], link[N], cnt = 1;
  int expand(int lst, char c) {
    int p = lst, d = c - 'a';
    if (int q = ch[p][d]) {
      if (len[p] + 1 == len[q]) {
        return q;
      } else {
        int tmp = ++cnt;
        len[tmp] = len[p] + 1, link[tmp] = link[q];
        memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[q] = tmp;
        return tmp;
      }
    } 
    int cur = ++cnt;
    len[cur] = len[p] + 1;
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
    return cur;
  }
} gsam;

int val[N], ans[N];

void update(int u, int idx) {
  for (; u && val[u] != idx && ~val[u]; u = gsam.link[u]) {
    if (val[u] != 0) val[u] = -1;
    else val[u] = idx;
  }
}

void solve() {
  std::cin >> n;
  for (int i = 1, lst = 1; i <= n; i++, lst = 1) {
    std::cin >> s[i];
    for (auto c : s[i]) lst = gsam.expand(lst, c);
  }

  for (int i = 1, lst = 1; i <= n; i++, lst = 1) {
    for (auto c : s[i]) lst = gsam.ch[lst][c - 'a'], update(lst, i);
  }
  for (int i = 2; i <= gsam.cnt; i++) {
    if (val[i] == -1) continue;
    ans[val[i]] += gsam.len[i] - gsam.len[gsam.link[i]];
  }

  for (int i = 1; i <= n; i++) std::cout << ans[i] << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
