/*
 * @file    P3649 [APIO2014] 回文串.cpp
 * @author  ForgotDream
 * @brief   PAM
 * @date    2024-01-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50;

struct PAM {
  int ch[N][26], len[N], nxt[N], cnt[N], tot, siz, lst;
  char s[N];
  void init() {
    tot = lst = 0;
    siz = -1;
    newNode(0), newNode(-1), nxt[0] = 1;
  }
  int newNode(int l) {
    len[++siz] = l, nxt[siz] = cnt[siz] = 0;
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
    lst = ch[cur][d], cnt[lst]++;
  }
} pam;

i64 lst = 0;

int n;
char s[N];

void solve() {
  std::cin >> (s + 1), n = strlen(s + 1);
  pam.init();
  for (int i = 1; i <= n; i++) pam.expand(s[i]);

  for (int i = pam.siz; ~i; i--) pam.cnt[pam.nxt[i]] += pam.cnt[i];

  i64 ans = 0;
  for (int i = 0; i <= pam.siz; i++) {
    ans = std::max(ans, 1ll * pam.cnt[i] * pam.len[i]);
  }
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
