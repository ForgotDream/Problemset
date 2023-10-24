/**
 * @file    LOJ#6490 「XXOI 2018」暑假时在做什么？有没有空？可以来学物理吗？.cpp
 * @author  ForgotDream
 * @brief   ST + 分治
 * @date    2023-10-10
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
constexpr i64 inf = 1e18;
int n, s, t, a[N];
i64 sum[N], f[N];
struct ST {
  i64 max[20][N], min[20][N];
  void init() {
    for (int i = 0; i <= n; i++) max[0][i] = min[0][i] = sum[i];
    for (int i = 1; i <= std::__lg(n); i++) {
      for (int j = 0; j <= n - (1 << i) + 1; j++) {
        max[i][j] = std::max(max[i - 1][j], max[i - 1][j + (1 << (i - 1))]);
        min[i][j] = std::min(min[i - 1][j], min[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  inline i64 queryMax(int l, int r) {
    if (l > r) return -inf;
    int d = std::__lg(r - l + 1);
    return std::max(max[d][l], max[d][r - (1 << d) + 1]);
  }
  inline i64 queryMin(int l, int r) {
    if (l > r) return inf;
    int d = std::__lg(r - l + 1);
    return std::min(min[d][l], min[d][r - (1 << d) + 1]);
  }
} st;
void solve(int l, int r) {
  if (r - l + 1 < s) return;
  if (l == r) {
    if (s == 1) f[l] = std::max(f[l], 1ll * a[l]);
    return;
  }
  int mid = (l + r) >> 1;
  solve(l, mid), solve(mid + 1, r);
  i64 pre = -inf, suf = -inf;
  for (int i = l; i <= mid; i++) {
    int x = i + s - 1, y = i + t - 1;
    pre = std::max(pre, st.queryMax(std::max(x, mid + 1), std::min(y, r)) - sum[i - 1]);
    f[i] = std::max(f[i], pre);
  }
  for (int i = r; i > mid; i--) {
    int x = i - t + 1, y = i - s + 1;
    suf = std::max(suf, sum[i] - st.queryMin(std::max(x, l) - 1, std::min(y, mid) - 1));
    f[i] = std::max(f[i], suf);
  }
}
void solve() {
  std::cin >> n >> s >> t;
  for (int i = 1; i <= n; i++) std::cin >> a[i], sum[i] = a[i] + sum[i - 1], f[i] = -inf;
  st.init();
  solve(1, n);
  for (int i = 1; i <= n; i++) std::cout << f[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
