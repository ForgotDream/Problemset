/**
 * @file    CF1823D Unique Palindromes.cpp
 * @author  ForgotDream
 * @brief   Constructions
 * @date    2023-04-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace MyFile {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}
}

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> x(k), c(k);
  for (int i = 0; i < k; i++) {
    std::cin >> x[i];
  }
  for (int i = 0; i < k; i++) {
    std::cin >> c[i];
  }

  for (int i = 0; i < k; i++) {
    if (x[i] < c[i]) {
      std::cout << "NO\n";
      return;
    }
  }

  std::vector<int> newx, newc;
  int prec = 0, prex = 0;
  for (int i = 0; i < k; i++) {
    if (c[i] != prec) {
      if (i != 0) {
        newx.push_back(prex);
        newc.push_back(prec);  
      }
      prec = c[i];
    }
    prex = x[i];
  }
  newx.push_back(prex), newc.push_back(prec);

  x = newx, c = newc;

  std::string ans = "", delta = "xy";
  int pre = 0, pivot = 0;
  for (int i = 0; i < x.size(); i++) {
    char ch = i + 'a';
    int cur = c[i] - pre;
    if (i == 0) {
      for (int i = 0; i < cur - 2; i++) {
        ans += ch;
        ++pivot;
      }
      if (pivot > x[i]) {
        std::cout << "NO\n";
        return;
      }
    } else {
      for (int i = 0; i < cur; i++) {
        ans += ch;
        ++pivot;
      }
      if (pivot > x[i]) {
        std::cout << "NO\n";
        return;
      }
    }
    int rst = (x[i] - pivot) / 3;
    for (int i = 0; i < rst; i++) {
      ans += delta + ch;
      pivot += 3;
    }
    if (pivot < x[i]) {
      ans += delta.substr(0, x[i] - pivot);
      if (x[i] - pivot == 1) {
        std::reverse(delta.begin(), delta.end());
      }
      pivot = x[i];
    }
    pre = c[i];
  }

  std::cout << "YES\n";
  std::cout << ans << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}