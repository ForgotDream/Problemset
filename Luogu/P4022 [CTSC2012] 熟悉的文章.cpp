/*
 * @file    P4022 [CTSC2012] 熟悉的文章.cpp
 * @author  ForgotDream
 * @brief   GSAM + DP + Monotonic Queue
 * @date    2024-01-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 50;

int n, m;

int f[N], g[N];

struct GSAM {
  int ch[N][2], len[N], link[N], cnt = 1;
  int expand(int lst, int d) {
    int p = lst;
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
  void match(std::string_view s) {
    int p = 1;
    for (int i = 1, cur = 0; i <= int(s.length()); i++) {
      int d = s[i - 1] - '0';
      while (p != 1 && !ch[p][d]) p = link[p], cur = len[p];
      if (ch[p][d]) p = ch[p][d], cur = std::min(cur + 1, len[p]);
      g[i] = cur;
    }
  }
} gsam;

std::string s;

bool check(int u) {
  static int q[N], hd = 1, tl = 0;

  for (int i = 0; i < u; i++) f[i] = 0;
  q[hd = tl = 1] = 0;
  for (int i = u; i <= int(s.length()); i++) {
    f[i] = f[i - 1];
    while (hd <= tl && f[i - u] - (i - u) >= f[q[tl]] - q[tl]) tl--;
    q[++tl] = i - u;
    while (hd <= tl && q[hd] < i - g[i]) hd++;
    if (hd <= tl) f[i] = std::max(f[i], f[q[hd]] + i - q[hd]);
  }

  return f[s.length()] * 10u >= s.length() * 9;
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1, lst = 1; i <= m; i++, lst = 1) {
    std::cin >> s;
    for (auto c : s) lst = gsam.expand(lst, c - '0');
  }

  for (int i = 1; i <= n; i++) {
    std::cin >> s;
    int lo = 0, hi = s.length(), ans = 0;
    gsam.match(s);
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      if (check(mid)) lo = mid + 1, ans = mid;
      else hi = mid - 1;
    }
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
