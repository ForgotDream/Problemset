/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>
#include <vector>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> h(n);
  for (auto &i : h) std::cin >> i;

  auto left  = [&](int i, int t = 1) { return (i + n - t) % n; };
  auto right = [&](int i, int t = 1) { return (i + t) % n; };

  for (int i = 0; i < n; i++) {
    std::vector<int> lmx(n), rmx(n);

    int mx = 0;
    for (int t = 1; t < n; t++) {
      mx = std::max(mx, h[left(i, t)]);
      lmx[left(i, t)] = mx;
    }

    mx = 0;
    for (int t = 1; t < n; t++) {
      mx = std::max(mx, h[right(i, t - 1)]);
      rmx[right(i, t)] = mx;
    }

    i64 ans = 0;
    for (int j = 0; j < n; j++) {
      if (j == i) continue;
      ans += std::min(lmx[j], rmx[j]);
    }
   
    std::cout << ans << " \n"[i == n - 1];
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
