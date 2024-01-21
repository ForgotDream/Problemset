#include <bits/stdc++.h>

using i64 = long long;

int n;

void solve() {
  std::cin >> n;
  int a = 0, b = 0;
  for (int i = 1, u; i <= n; i++) std::cin >> u, a += u, std::cin >> u, b += u;
  if (a > b) std::cout << "Takahashi\n";
  else if (a < b) std::cout << "Aoki\n";
  else std::cout << "Draw\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
