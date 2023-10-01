#include <iostream>

using i64 = long long;

constexpr int N = 305;
int n, h, x[N], p[N], f[N];
int dp[N][N];
void solve() {
  std::cin >> n >> h;
  for (int i = 1; i <= n; i++) std::cin >> x[i];
  for (int i = 1; i <= n; i++) std::cin >> p[i] >> f[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}