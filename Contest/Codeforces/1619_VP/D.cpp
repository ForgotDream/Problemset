#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

int m, n;
std::vector<std::vector<int>> p;
bool check(int val) {
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      
    }
  }
  return true;
}
void solve() {
  std::cin >> m >> n;
  p.resize(m + 1, std::vector<int>(n + 1));
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) std::cin >> p[i][j];
    std::sort(p[i].begin() + 1, p[i].end());
  }
  int lo = 1, hi = 1e9, ans = lo;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) lo = mid + 1, ans = mid;
    else hi = mid - 1;
  }
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}