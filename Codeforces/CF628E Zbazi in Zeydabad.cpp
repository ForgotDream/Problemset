/**
 * @file    CF628E Zbazi in Zeydabad.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-10-27
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 3050;
int n, m, a[N][N];
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= m; i += (i & -i)) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= (i & -i)) res += tree[i];
    return res;
  }
} bit[N * 2];
int fl[N][N], fr[N][N], fd[N][N];
std::vector<pii> seg[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      std::cin >> c;
      a[i][j] = (c == 'z');
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j]) fl[i][j] = fl[i][j - 1] + 1;
    }
    for (int j = m; j >= 1; j--) {
      if (a[i][j]) fr[i][j] = fr[i][j + 1] + 1;
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j]) fd[i][j] = fd[i + 1][j - 1] + 1;
      int r = j + fr[i][j] - 1;
      if (j <= r) seg[r].emplace_back(i, j);
    }
  }
  i64 ans = 0;
  for (int j = m; j >= 1; j--) {
    for (auto [l, r] : seg[j]) bit[l + r].modify(r, 1);
    for (int i = 1; i <= n; i++) {
      if (!a[i][j]) continue;
      int lim = std::min(fl[i][j], fd[i][j]);
      int l = j - lim + 1, r = j;
      ans += bit[i + j].query(r) - bit[i + j].query(l - 1);
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
