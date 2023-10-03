#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <numeric>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 70;
pii pos[N];
int n;
int dis(pii u, pii v) {
  return std::abs(u.first - v.first) + std::abs(u.second - v.second);
}
namespace N_LESS_THAN_20 {
constexpr int N = 21, inf = 0x3f3f3f3f;
int f[1 << N];
void solve() {
  std::memset(f, 0x3f, sizeof(f));
  int mask = (1 << n) - 1;
  for (int i = 1; i <= n; i++) f[1 << (i - 1)] = 0;
  for (int i = 0; i <= mask; i++) {
    for (int j = 1; j <= n; j++) {
      if (i & (1 << (j - 1))) continue;
      int cur = 0;
      for (int k = 1; k <= n; k++) {
        if (!(i & (1 << (k - 1)))) continue;
        cur = std::max(cur, dis(pos[j], pos[k]));
      }
      int p = i | (1 << (j - 1));
      f[p] = std::min(f[p], f[i] + cur);
    }
  }
  int ans = f[mask];
  std::cout << ans / 2 << "\n";
}
}  // namespace N_LESS_THAN_20
namespace FULL_COMBO {
void solve() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {

    }
  }
}
} //  namespace FULL_COMBO
void solve() {
  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) {
      char c;
      std::cin >> c;
      if (c == '#') pos[++n] = pii(i + j, i - j);
    }
  }
  if (n <= 20) N_LESS_THAN_20::solve();
  else FULL_COMBO::solve();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
