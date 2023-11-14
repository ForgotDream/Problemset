#include <bits/stdc++.h>

using i64 = long long;

int n = 20, q = 20;
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution w(1, 200), idx(1, n);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << n << "\n";
  for (int i = 1; i <= n; i++) std::cout << w(rng) << " \n"[i == n];
  std::cout << q << "\n";
  for (int l, r, m; q; q--) {
    l = idx(rng), r = idx(rng), m = w(rng);
    if (l > r) std::swap(l, r);
    std::cout << l << " " << r << " " << m << "\n";
  }
  return 0;
}
