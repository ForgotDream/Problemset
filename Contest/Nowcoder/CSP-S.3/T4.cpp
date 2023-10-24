#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 5e4 + 50;
int n, m, q;
i64 a[N], b[N], d[N], e[N];
std::vector<std::vector<i64>> c;
namespace P20 {
void solve() {
  while (q--) {
    int l1, r1, l2, r2;
    std::cin >> l1 >> r1 >> l2 >> r2;
    std::vector f(n + 1, std::vector<i64>(m + 1, -1e18));
    f[l1 - 1][l2 - 1] = 0;
    for (int i = l1 - 1; i <= r1; i++) {
      for (int j = l2 - 1; j <= r2; j++) {
        if (i != l1 - 1) f[i][j] = std::max(f[i][j], f[i - 1][j] + d[i]);
        if (j != l2 - 1) f[i][j] = std::max(f[i][j], f[i][j - 1] + e[j]);
        if (i != l1 - 1 && j != l2 - 1)
          f[i][j] = std::max(f[i][j], f[i - 1][j - 1] + c[i][j]);
      }
    }
    std::cout << f[r1][r2] << "\n";
  }
}
}  // namespace P20
namespace P40 {
i64 st[20][N];
i64 sum[N];
int logn[N];
void init() {
  logn[1] = 0, logn[2] = 1;
  for (int i = 3; i < N; i++) logn[i] = logn[i / 2] + 1;
  for (int i = 1; i <= m; i++) st[0][i] = c[1][i] - b[i];
  for (int i = 1; i <= logn[m]; i++) {
    for (int j = 1; j <= m - (1 << i) + 1; j++) {
      st[i][j] = std::max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}
i64 query(int l, int r) {
  int d = logn[r - l + 1];
  return std::max(st[d][l], st[d][r - (1 << d) + 1]);
}
void solve() {
  init();
  for (int i = 1; i <= m; i++) sum[i] = sum[i - 1] + e[i];
  while (q--) {
    int l1, r1, l2, r2;
    std::cin >> l1 >> r1 >> l2 >> r2;
    std::cout << sum[r2 - l2 + 1] + std::max(d[1], query(l2, r2)) << "\n";
  }
}
}  // namespace P40
void solve() {
  std::cin >> n >> m >> q;
  c = std::vector(n + 1, std::vector<i64>(m + 1));
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) std::cin >> b[i];
  for (int i = 1; i <= n; i++) std::cin >> d[i];
  for (int i = 1; i <= m; i++) std::cin >> e[i];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> c[i][j];
      c[i][j] = a[i] + b[j] - c[i][j];
    }
  }
  if (n * m <= 1e3 && q <= 1e3)
    P20::solve();
  else if (n == 1)
    P40::solve();
}

int main() {
  std::freopen("ex_produce4.in", "r", stdin);
  std::freopen("tmp.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
