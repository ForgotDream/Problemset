/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

i64 A, B, M;

void solve() {
  std::cin >> A >> B;
  
  i64 C = A - 2 * B;
  if (C <= 0) {
    std::cout << 0 << "\n";
    return;
  }
  std::cerr << C << "\n";

  i64 p = 61;
  while (!(C >> p & 1)) p--;

  i64 ans = (1ll << (__builtin_popcount(C) - 1)) % M * (1ll << p) % M;
  std::cout << ans << "\n";

  for (int i = 1; i <= n; i++) {
    
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t >> M;
  while (t--) solve();

  return 0;
}
