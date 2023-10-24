#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <queue>

using i64 = long long;
using f80 = long double;
using tfi2 = std::tuple<double, int, int>;

constexpr int N = 105;
constexpr double eps = 1e-6;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m, sx, sy, tx, ty;
int a[N][N];
double s, dis[N][N];
bool vis[N][N];
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
bool check(f80 mid) {
  std::priority_queue<tfi2, std::vector<tfi2>, std::greater<>> pq;
  memset(vis, false, sizeof(vis)), memset(dis, 0x63, sizeof(dis));
  dis[sx][sy] = 0, pq.emplace(0, sx, sy);
  while (!pq.empty()) {
    auto [_, x, y] = pq.top();
    pq.pop();
    if (vis[x][y]) continue;
    vis[x][y] = true;
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy)) continue;
      double w;
      if (i < 2) w = mid;
      else w = 1;
      if (dis[dx][dy] > dis[x][y] + w) {
        dis[dx][dy] = dis[x][y] + w;
        pq.emplace(dis[dx][dy], dx, dy);
      }
    }
  }
  return dis[tx][ty] >= s;
}
void solve() {
  std::cin >> n >> m >> sx >> sy >> tx >> ty;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) std::cin >> a[i][j];
  }
  std::cin >> s;
  f80 lo = 0, hi = 1e5;
  while (fabs(hi - lo) > eps) {
    f80 mid = (lo + hi) / 2;
    if (check(mid)) hi = mid;
    else lo = mid;
  }
  std::cout << std::fixed << std::setprecision(3) << lo << "\n";
}

int main() {
  freopen("msg.in", "r", stdin);
  freopen("msg.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
