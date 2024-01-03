/*
 * @file    P3592 [POI2015] MYJ.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2024-01-01
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 55, M = 405;
int n, m;

struct Query {
  int l, r, v;
} qry[M];
std::vector<int> b;

inline int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}

int f[N][N][M], buc[N][N];
int pos[N][N][M], val[N][N][M];

int ans[N];
void dfs(int l, int r, int k) {
  if (l > r) return;
  ans[pos[l][r][k]] = b[val[l][r][k] - 1];
  dfs(l, pos[l][r][k] - 1, val[l][r][k]);
  dfs(pos[l][r][k] + 1, r, val[l][r][k]);
}

void solve() {
  std::cin >> n >> m;

  for (int i = 1; i <= m; i++) {
    auto &[l, r, v] = qry[i];
    std::cin >> l >> r >> v, b.push_back(v);
  }

  std::sort(b.begin(), b.end());
  // b.erase(std::unique(b.begin(), b.end()));
  for (int i = 1; i <= m; i++) qry[i].v = find(qry[i].v);

  for (int i = m; i; i--) {
    for (int j = 1; j <= m; j++) {
      if (qry[j].v != i) continue;
      for (int l = 1; l <= qry[j].l; l++) {
        for (int r = qry[j].r; r <= n; r++) {
          buc[l][r]++;
        }
      }
    }
    for (int len = 1; len <= n; len++) {
      for (int l = 1; l <= n - len + 1; l++) {
        int r = l + len - 1;
        f[l][r][i] = f[l][r][i + 1], pos[l][r][i] = pos[l][r][i + 1];
        val[l][r][i] = val[l][r][i + 1];
        for (int k = l; k <= r; k++) {
          int coef = buc[l][r] - buc[l][k - 1] - buc[k + 1][r];
          int cur = f[l][k - 1][i] + f[k + 1][r][i] + coef * b[i - 1];
          if (cur > f[l][r][i]) {
            f[l][r][i] = cur, pos[l][r][i] = k, val[l][r][i] = i;
          }
        }
        if (!val[l][r][i]) pos[l][r][i] = l, val[l][r][i] = i;
      }
    }
  }

  std::cout << f[1][n][1] << "\n";
  dfs(1, n, 1);
  for (int i = 1; i <= n; i++) std::cout << ans[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
