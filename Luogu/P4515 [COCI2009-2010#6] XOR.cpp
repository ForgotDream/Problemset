/**
 * @file    P4515 [COCI2009-2010#6] XOR.cpp
 * @author  ForgotDream
 * @brief   Inclusion-Exclusion + Combination
 * @date    2023-11-29
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 15;
int n;
i64 x[N], y[N], r[N], c[N], ans;
void solve() {
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i] >> r[i];
    c[i] = x[i] + y[i] + r[i];
  }
  int mask = (1 << n) - 1;
  for (int i = 1; i <= mask; i++) {
    // int cnt = std::popcount(uint32_t(i));
    int cnt = __builtin_popcount(i);
    i64 cx = 0, cy = 0, cc = 1e18;
    bool flg = true;
    for (int j = 0; j < n; j++) {
      if (!(i & (1 << j))) continue;
      cx = std::max(cx, x[j]), cy = std::max(cy, y[j]), cc = std::min(cc, c[j]);
      if (cx + cy >= cc) {
        flg = false;
        break;
      }
    }
    if (!flg) continue;
    if (cnt & 1) ans += (1ll << (cnt - 1)) * (cc - cx - cy) * (cc - cx - cy);
    else ans -= (1ll << (cnt - 1)) * (cc - cx - cy) * (cc - cx - cy);
  }
  std::cout << std::fixed << std::setprecision(1) << (ans / 2.) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
