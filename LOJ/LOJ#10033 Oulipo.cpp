/**
 * @file    LOJ#10033 Oulipo.cpp
 * @author  ForgotDream
 * @brief   字符串 Hash
 * @date    2023-04-02
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

void solve() {
  std::string s, t;
  std::cin >> t >> s;

  if (s.length() < t.length()) {
    std::cout << 0 << "\n";
    return;
  }

  std::mt19937 rnd(std::time(nullptr));
  i64u base = rnd() % 2000 + 200;

  std::vector<i64u> pow(1e4 + 50);
  pow[0] = 1;
  for (int i = 1; i <= 1e4; i++) {
    pow[i] = pow[i - 1] * base;
  }

  int tLen = t.length();
  i64u tHash = 0;
  for (int i = 0; i < tLen; i++) {
    tHash += pow[tLen - i - 1] * (t[i] - 'A');
  }

  int sLen = s.length();
  i64u curHash = 0;
  for (int i = 0; i < tLen; i++) {
    curHash += pow[tLen - i - 1] * (s[i] - 'A');
  }

  int res = 0;
  if (curHash == tHash) {
    res++;
  }

  for (int i = tLen; i < sLen; i++) {
    curHash = base * (curHash - pow[tLen - 1] * (s[i - tLen] - 'A')) + (s[i] - 'A');
    if (curHash == tHash) {
      res++;
    }
  }

  std::cout << res << "\n";
  return;
}

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}