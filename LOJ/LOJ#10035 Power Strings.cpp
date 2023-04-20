/**
 * @file    LOJ#10035 Power Strings.cpp
 * @author  ForgotDream
 * @brief   KMP
 * @date    2023-04-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

void solve(const std::string &s) {
  int len = s.length();
  std::vector<int> nxt(len);

  for (int i = 1; i < len; i++) {
    int j = nxt[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = nxt[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    nxt[i] = j;
  }

  if (len % (len - nxt[len - 1]) == 0) {
    std::cout << len / (len - nxt[len - 1]) << "\n";
  } else {
    std::cout << 1 << "\n";
  }

  return;
}

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  while (std::cin >> s && s != ".") {
    solve(s);
  }

  return 0;
}