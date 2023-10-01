#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 105;
int n;
char s[3][N];
void solve() {
  std::cin >> n >> s[0] >> s[1] >> s[2];
  int ans = 1e9;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (!(s[0][i] == s[1][j] && s[1][j] == s[2][k])) continue;
        int tmp = std::max({i, j, k});
        if (i == j && j == k) tmp += 2 * n;
        else if (i == j || j == k || i == k) tmp = n + std::min({i, j, k});
        ans = std::min(ans, tmp);
      }
    }
  }
  if (ans == 1e9) std::cout << -1 << "\n";
  else std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}