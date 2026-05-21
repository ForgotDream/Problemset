/*
 * @file    
 * @author  forgotdream
 * @brief   
 * @date    2024-02-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

std::vector<i64> pw;

void init() {
  pw.push_back(1);
  while (true) {
    pw.push_back(3 * pw.back());
    if (pw.back() > 1e9) break;
  }
  std::reverse(pw.begin(), pw.end());
}

void solve() {
  int n;
  std::cin >> n;

  int p = pw.size() - 1;
  i64 ans = 0;

  for (auto i : pw) {
    while (n >= i) {
      ans += 3 * i + p * i / 3;
      n -= i;
    }
    p--;
  }

  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  init();

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
