/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

struct PAM {
  int ch[N][26], len[N], nxt[N], cnt, lst, tot;
  char s[N];

  void init() {
    tot = lst = 0;
  }

  int get_nxt() {
    int u = lst;
    while (s[tot] != s[tot - len[u] - 1]) u = nxt[u];
    return u;
  }
} pam;

void solve() {
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
