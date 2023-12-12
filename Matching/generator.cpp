#include <bits/stdc++.h>

using i64 = long long;

int n = 10, T = 100;
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution ui(1, 20);
void solve() {
  std::cout << n << " " << T << "\n";
  for (int i = 1; i <= n; i++) std::cout << ui(rng) << " " << ui(rng) << " " << ui(rng) << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
