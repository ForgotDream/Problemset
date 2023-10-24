/**
 * @file    LOJ#10047 似乎在梦中见过的样子.cpp
 * @author  ForgotDream
 * @brief   KMP
 * @date    2023-04-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

std::vector<int> prefixFunction(const std::string &s) {
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

  return nxt;
}

int solve(const std::string &s, int k) {
  int res = 0, len = s.length();
  auto nxt = prefixFunction(s);

  for (int i = 2 * k; i < len; i++) {
    int pivot = nxt[i];
    if (pivot < k) {
      continue;
    }
    while (pivot >= k) {
      if (2 * pivot <= i) {
        res++;
        break;
      } else {
        pivot = nxt[pivot - 1];
      }
    }
  }

  return res;
}

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  int k;

  std::cin >> s >> k;

  int ans = 0;
  for (int i = 0; i < s.length(); i++) {
    ans += solve(s.substr(i), k);
  }

  std::cout << ans << "\n";

  return 0;
}