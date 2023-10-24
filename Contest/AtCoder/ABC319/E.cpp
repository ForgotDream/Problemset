#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 1e6 + 50;
int n, q;
i64 p[N], t[N], x, y;
i64 lcm = 1, ans[M];
i64 calc(i64 st) {
  i64 res = st + x;
  for (int i = 1; i < n; i++) {
    i64 nxt = p[i] * ((res - 1) / p[i] + 1);
    res = nxt + t[i];
  }
  return res + y;
}
void solve() {
  std::cin >> n >> x >> y;
  for (int i = 1; i < n; i++) {
    std::cin >> p[i] >> t[i], lcm = std::lcm(lcm, p[i]);
  }
  for (int i = 0; i < lcm; i++) ans[i] = calc(i);
  std::cin >> q;
  while (q--) {
    i64 s;
    std::cin >> s;
    std::cout << ans[s % lcm] + s / lcm * lcm << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}