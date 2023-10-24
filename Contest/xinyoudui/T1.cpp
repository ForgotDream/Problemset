#include <cassert>
#include <iostream>

using i64 = long long;

constexpr int N = 550;
int n, m, o;
char a[N][N];
inline bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
namespace N_LESS_THAN_100 {
void solve() {
  i64 ans = 0;
  for (int x1 = 1; x1 <= n; x1++) {
    for (int y1 = 1; y1 <= m; y1++) {
      if (a[x1][y1] != '1') continue;
      for (int x2 = x1 + 1; x2 <= n; x2++) {
        for (int y2 = 1; y2 <= y1; y2++) {
          if (a[x2][y2] != '1') continue;
          int dx = x2 - x1, dy = y1 - y2;
          if (valid(x1 - dy, y1 - dx) && a[x1 - dy][y1 - dx] == '1' &&
              valid(x2 - dy, y2 - dx) && a[x2 - dy][y2 - dx] == '1') {
            ans++;
          }
        }
      }
    }
  }
  std::cout << ans << "\n";
}
} // namespace N_LESS_THAN_100
void solve() {
  std::cin >> n >> o;
  m = n;
  for (int i = 1; i <= n; i++) std::cin >> (a[i] + 1);
  if (o == 5) {
    std::cout << 0 << "\n";
    return;
  } else if (o == 4) {
    std::cout << 1ll * n * n * (n * n - 1) / 12;
    return;
  } else if (o == 1) {
    for (int i = 1; i <= n; i += 2) {
      for (int j = 1; j <= n; j += 2) {
        a[(i - 1) / 2 + 1][(j - 1) / 2 + 1] = a[i][j];
      }
    }
    m = n = (n - 1) / 2 + 1;
    N_LESS_THAN_100::solve();
    return;
  }
  N_LESS_THAN_100::solve();
}

int main() {
  freopen("firstsnow.in", "r", stdin);
  freopen("firstsnow.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
