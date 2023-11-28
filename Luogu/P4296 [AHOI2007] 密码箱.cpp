/**
 * @file    P4296 [AHOI2007] 密码箱.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using u32 = uint32_t;

constexpr int N = 1e7 + 50, M = 2e6 + 50;
u32 n;
std::vector<u32> ans;
void solve() {
  std::cin >> n;
  if (n == 1) return std::cout << "None\n", void();
  ans.push_back(1);
  for (u32 i = 1; 1ll * i * i < n; i++) {
    if (n % i != 0) continue;
    int a = i, b = n / i;
    for (u32 j = b + 1; 1ll * j <= n; j += b) if ((j + 1) % a == 0) ans.push_back(j);
    for (u32 j = b - 1; 1ll * j <= n; j += b) if ((j - 1) % a == 0) ans.push_back(j);
  }
  std::sort(ans.begin(), ans.end());
  ans.erase(std::unique(ans.begin(), ans.end()), ans.end());
  for (auto i : ans) std::cout << i << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
