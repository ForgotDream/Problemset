#include <bits/stdc++.h>

using i64 = long long;

static const i64 INF = 0x3f3f3f3f3f3f3f3f;
struct Mail {
  i64 x, y, cnt;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, k;
  std::cin >> n >> k;
  std::vector<Mail> a(n);
  std::vector<i64> cost(1 << n | 1), maxX(1 << n | 1), maxY(1 << n | 1), num(1 << n | 1);
  std::vector<std::vector<i64>> f(1 << n | 1);

  for (auto &i : a) {
    std::cin >> i.x >> i.y >> i.cnt;
  }

  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      if (!(i & (1 << j))) {
        maxX[i | (1 << j)] = std::max(maxX[i | (1 << j)], a[j].x);
        maxY[i | (1 << j)] = std::max(maxY[i | (1 << j)], a[j].y);
        num[i | (1 << j)] = num[i] + a[j].cnt;
        cost[i | (1 << j)] = cost[i] + a[j].x * a[j].y * a[j].cnt;
      }
    }
  }

  for (int i = 0; i < (1 << n); i++) {
    cost[i] = num[i] * maxX[i] * maxY[i] - cost[i];
  }

  for (int i = 0; i < (1 << n); i++) {
    f[i].resize(k + 1);
    for (int j = 0; j <= k; j++) {
      f[i][j] = INF;
    }
  }

  for (int i = 1; i < (1 << n); i++) {
    f[i][1] = cost[i];
  }

  for (int i = 1; i < (1 << n); i++) {
    for (int j = 1; j < k; j++) {
      for (int k = i; k; k = (k - 1) & i) {
        f[i][j + 1] = std::min(f[i][j + 1], f[k][j] + cost[i ^ k]);
      }
    }
  }

  std::cout << f[(1 << n) - 1][k] << '\n';

  return 0;
}