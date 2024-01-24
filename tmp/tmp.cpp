/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using f64 = double;

constexpr int N = 70;

int n, m, s[N];
f64 k, c[N];

void solve() {
  std::cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) std::cin >> s[i];
  for (int i = 1; i <= n; i++) std::cin >> c[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t >> *new int;
  while (t--) solve();

  return 0;
}
