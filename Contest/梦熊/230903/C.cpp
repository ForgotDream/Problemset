#include <iostream>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n, a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::cout << n + 1 << "\n";
}

int main() {
  std::freopen("list.in", "r", stdin);
  std::freopen("list.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}