/**
 * @file    P4027 [NOI2007] 货币兑换.cpp
 * @author  ForgotDream
 * @brief   Lichao SegTree + DP
 * @date    2023-10-28
 */
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

using i64 = long long;
using f80 = long double;

constexpr int N = 1e5 + 50;
int n, s;
f80 a[N], b[N], rate[N];
std::vector<f80> c;
int find(f80 u) {
  return std::lower_bound(c.begin(), c.end(), u) - c.begin();
}
struct Line {
  f80 k, b;
  f80 operator()(const f80 &val) const { return k * val + b; }
} line[N];
struct SegTree {
  int id[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void modify(int s, int t, int u, int val) {
    int &cur = id[u], mid = (s + t) >> 1;
    if (!cur) return cur = val, void();
    if (line[val](c[mid]) > line[cur](c[mid])) std::swap(val, cur);
    if (line[val](c[s]) > line[cur](c[s])) modify(s, mid, lc(u), val);
    if (line[val](c[t]) > line[cur](c[t])) modify(mid + 1, t, rc(u), val);
  }
  f80 query(int tar, int s, int t, int u) {
    if (s == t) return line[id[u]](c[tar]);
    int mid = (s + t) >> 1;
    f80 res = line[id[u]](c[tar]);
    if (mid >= tar) return std::max(res, query(tar, s, mid, lc(u)));
    else return std::max(res, query(tar, mid + 1, t, rc(u)));
  }
} seg;
f80 f[N];
void solve() {
  std::cin >> n >> f[0];
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i] >> b[i] >> rate[i];
    c.emplace_back(a[i] / b[i]);
  }
  std::sort(c.begin(), c.end());
  for (int i = 1; i <= n; i++) {
    int u = find(a[i] / b[i]);
    f[i] = std::max(f[i - 1], b[i] * seg.query(u, 0, n - 1, 1));
    f80 tmp = a[i] * rate[i] + b[i];
    line[i] = {f[i] * rate[i] / tmp, f[i] / tmp};
    seg.modify(0, n - 1, 1, i);
  }
  std::cout << std::fixed << std::setprecision(3) << f[n] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
