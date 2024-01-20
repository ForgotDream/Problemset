/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

int n, m;
char s[N];

int pos[N];

struct SAM {
  int ch[N][26], link[N], len[N], cnt = 1, lst = 1;
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
        memcpy(ch[tmp], ch[q], sizeof(ch[q]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }
} sam;

void solve() {
  std::cin >> n >> m >> (s + 1);
  for (int i = n; i >= 1; i--) pos[i] = sam.expand(s[i] - 'a');

  for (int i = 1, k, l; i <= m; i++) {
    std::cin >> k >> l;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
