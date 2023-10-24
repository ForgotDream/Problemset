#include <iostream>

using i64 = long long;

constexpr int N = 105;
int n;
bool a[N][N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    int x1, x2, y1, y2;
    std::cin >> x1 >> x2 >> y1 >> y2;
    for (int x = x1; x < x2; x++) {
      for (int y = y1; y < y2; y++) {
        a[x][y] = true;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= 100; i++) {
    for (int j = 0; j <= 100; j++) {
      ans += a[i][j];
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}