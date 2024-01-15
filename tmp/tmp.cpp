/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-15
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

int n, m, q;
char s[N], t[N];

int la[N], ra[N], lb[N], rb[N];

struct SAM {
  int ch[N][26], len[N], link[N], cnt = 1, lst = 1;
  void expand(char c) {
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
  }
} sam;

void solve() {
  std::cin >> (s + 1) >> n;
  for (int i = 1; i <= n; i++) std::cin >> la[i] >> ra[i];
  std::cin >> (t + 1) >> m;
  for (int i = 1; i <= m; i++) std::cin >> lb[i] >> rb[i];

  std::cin >> q;
  for (int i = 1, u, v; i <= q; i++) {
    std::cin >> u >> v;
  }
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
