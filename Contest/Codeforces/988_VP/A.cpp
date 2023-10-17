#include <algorithm>
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 105;
int n, k, a[N], p[N];
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::iota(p + 1, p + n + 1, 1);
  std::sort(p + 1, p + n + 1, [&](int lhs, int rhs) {
    return a[lhs] < a[rhs];
  });
  int m = std::unique(p + 1, p + n + 1, [&](int lhs, int rhs) {
    return a[lhs] == a[rhs];
  }) - p - 1;
  if (m < k) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
  for (int i = 1; i <= k; i++) std::cout << p[i] << " \n"[i == k];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
