#include <algorithm>
#include <iostream>
#include <stack>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, a[N], b[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) std::cin >> b[i];
  std::sort(b + 1, b + m + 1, std::greater<>());
  int p = 1;
  for (int i = 1; i <= n; i++) {
    while (b[p] > a[i] && p <= m) std::cout << b[p++] << " ";
    std::cout << a[i] << " ";
  }
  while (p <= m) std::cout << b[p++] << " ";
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
