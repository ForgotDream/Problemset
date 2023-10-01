#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
constexpr int N = 5e5 + 50;
int n, m;
u64 h[N], v[N];
namespace _30 {
void solve() {
  for (int i = 1; i <= m; i++) {
    for (int i = 1; i <= n; i++) h[i] += v[i];
    int opt, l, r;
    u64 v;
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> l >> r >> v;
      for (int i = l; i <= r; i++) ::v[i] += v;
    } else {
      std::cin >> l >> r;
      u64 res = 0;
      for (int i = l; i <= r; i++) res += h[i];
      std::cout << res << "\n";
    }
  }
}
}
namespace _50 {
void solve() {
  for (int i = 1; i <= n; i++) h[i] += h[i - 1], v[i] += v[i - 1];
  for (int i = 1; i <= m; i++) {
    int opt, l, r, v;
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> l >> r >> v;
    } else {
      std::cin >> l >> r;
      std::cout << h[r] - h[l - 1] + m * (::v[r] - ::v[l - 1]) << "\n";
    }
  }
}
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> h[i] >> v[i];
  if (n <= 5000 && m <= 5000) _30::solve();
  else _50::solve();
  return 0;
}