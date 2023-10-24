#include <algorithm>
#include <iostream>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 5050;
int n, k;
pii a[N];
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].first >> a[i].second;
  }
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= std::min(i, k); j++) {
      
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
