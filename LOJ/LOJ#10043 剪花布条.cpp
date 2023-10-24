/**
 * @file    LOJ#10043 剪花布条.cpp
 * @author  ForgotDream
 * @brief   KMP
 * @date    2023-04-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

static char s[1050], t[1050];

void solve() {
  scanf("%s", t);

  int n = std::strlen(s), m = std::strlen(t);

  std::vector<int> nxt(n);
  int j = 0;
  nxt[0] = 0;

  for (int i = 1; i < m; i++) {
    while (j > 0 && t[j] != t[i]) {
      j = nxt[j] - 1;
    }
    if (t[j] == t[i]) {
      j++;
    }
    nxt[i] = j;
  }

  int ans = 0;
  j = 0;
  for (int i = 0; i < n; i++) {
    while (j > 0 && s[i] != t[j]) {
      j = nxt[j];
    }
    if (s[i] == t[j]) {
      j++;
    }
    if (j == m) {
      ans++;
      j = 0;
    }
  }

  printf("%d\n", ans);

  return;
}

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  while (scanf("%s", s) && (s[0] != '#' || s[1] != '\0')) {
    solve();
  }

  return 0;
}