/*
 * @file    P4555 [国家集训队] 最长双回文串.cpp
 * @author  ForgotDream
 * @brief   PAM
 * @date    2024-01-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

struct PAM {
  int ch[N][26], len[N], nxt[N], tot, siz, lst;
  char s[N];
  void init() {
    siz = -1, tot = lst = 0;
    newNode(0), newNode(-1), nxt[0] = 1;
  }
  int newNode(int l) {
    len[++siz] = l, nxt[siz] = 0;
    memset(ch[siz], 0, sizeof(ch[siz]));
    return siz;
  }
  int getNxt(int u) {
    while (s[tot - len[u] - 1] != s[tot]) u = nxt[u];
    return u;
  }
  void expand(char c) {
    s[++tot] = c;
    int cur = getNxt(lst), d = c - 'a';
    if (!ch[cur][d]) {
      int p = newNode(len[cur] + 2);
      nxt[p] = ch[getNxt(nxt[cur])][d];
      ch[cur][d] = p;
    }
    lst = ch[cur][d];
  }
} cis, trans;

int n;
char s[N];

int f[N], g[N];

void solve() {
  std::cin >> (s + 1), n = strlen(s + 1);

  cis.init(), trans.init();
  for (int i = 1; i <= n; i++) cis.expand(s[i]), f[i] = cis.len[cis.lst];

  std::reverse(s + 1, s + n + 1);
  for (int i = 1; i <= n; i++) trans.expand(s[i]), g[i] = trans.len[trans.lst];
  std::reverse(g + 1, g + n + 1);

  int ans = 0;
  for (int i = 1; i < n; i++) ans = std::max(ans, f[i] + g[i + 1]);
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
