#include <iostream>

using i64 = long long;

constexpr int N = 205;
int n;
i64 a[N], b[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  a[0] = -3e18, a[n + 1] = 3e18;
  for (int i = 0; i <= n; i++) {
    
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}