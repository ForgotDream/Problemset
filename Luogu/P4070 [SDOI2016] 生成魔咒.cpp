/*
 * @file    P4070 [SDOI2016] 生成魔咒.cpp
 * @author  ForgotDream
 * @brief   SAM
 * @date    2024-01-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

struct SAM {
  std::map<int, int> ch[N];
  int link[N], len[N], cnt, lst;
  void init() { link[0] = -1, len[0] = cnt = lst = 0; }
  void expand(int c) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1;
    int p = lst;
    for (; ~p && !ch[p].count(c); p = link[p]) ch[p][c] = cur;
    if (p == -1) return link[cur] = 0, lst = cur, void();
    int q = ch[p][c];
    if (len[p] + 1 == len[q]) {
      link[cur] = q;
    } else {
      int tmp = ++cnt;
      len[tmp] = len[p] + 1, link[tmp] = link[q];
      ch[tmp] = ch[q];
      for (; ~p && ch[p][c] == q; p = link[p]) ch[p][c] = tmp;
      link[q] = link[cur] = tmp;
    }
    lst = cur;
  }
} sam;

int n;
i64 ans = 0;

void solve() {
  std::cin >> n, sam.init();
  for (int u; n; n--) {
    std::cin >> u, sam.expand(u);
    ans += sam.len[sam.lst] - sam.len[sam.link[sam.lst]];
    std::cout << ans << "\n";
  }
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
