#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  i64 n, k, g;
  std::cin >> n >> k >> g;
  i64 d = std::ceil(1. * g / 2);
  i64 cost = std::min((n - 1) * (d - 1), k * g), rst = k * g - cost;
  i64 ans = 0;
  if (rst % g >= d) {
    ans = rst + g - rst % g;
  } else {
    ans = rst - rst % g;
  }
  std::cout << k * g - ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) { solve(); }

  return 0;
}
