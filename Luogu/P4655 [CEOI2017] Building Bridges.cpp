/**
 * @file    P4655 [CEOI2017] Building Bridges.cpp
 * @author  ForgotDream
 * @brief   Lichao SegTree + DP
 * @date    2023-10-27
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50, S = -1e6, T = 1e6;
int n;
i64 h[N], w[N], s[N], f[N];
struct Line {
  i64 k, b;
  i64 operator()(const i64 &val) const { return k * val + b; }
} line[N];
struct SegTree {
  struct Node {
    int lc, rc, id;
  } tree[N << 5];
  int cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void modify(int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    int &cur = tree[u].id, mid = (s + t) >> 1;
    if (!cur) return cur = val, void();
    if (line[val](mid) < line[cur](mid)) std::swap(val, cur);
    if (line[val](s) < line[cur](s)) modify(s, mid, lc(u), val);
    if (line[val](t) < line[cur](t)) modify(mid + 1, t, rc(u), val);
  }
  i64 query(int tar, int s, int t, int u) {
    if (!u) return 1e18;
    if (s == t) return line[tree[u].id](tar);
    i64 res = line[tree[u].id](tar);
    int mid = (s + t) >> 1;
    if (mid >= tar) return std::min(res, query(tar, s, mid, lc(u)));
    else return std::min(res, query(tar, mid + 1, t, rc(u)));
  }
} seg;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> h[i];
  for (int i = 1; i <= n; i++) std::cin >> w[i], s[i] = s[i - 1] + w[i];
  int rt = 0;
  for (int i = 1; i <= n; i++) {
    if (i == 1) f[i] = h[i] * h[i];
    else f[i] = seg.query(h[i], S, T, rt) + s[i - 1] + h[i] * h[i];
    line[i] = {-2 * h[i], f[i] - s[i] + h[i] * h[i]};
    seg.modify(S, T, rt, i);
  }
  // for (int i = 1; i <= n; i++) std::cout << f[i] << " \n"[i == n];
  std::cout << f[n] - f[1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
