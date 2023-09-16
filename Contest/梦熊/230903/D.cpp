#include <iostream>

using i64 = long long;

constexpr int N = 50;
int n, m;
char a[N][N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> (a[i] + 1);
  std::cout << n + m - 1 << "\n";
}

int main() {
  std::freopen("plant.in", "r", stdin);
  std::freopen("plant.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}