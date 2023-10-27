/**
 * @file    CF678F Lena and Queries.cpp
 * @author  ForgotDream
 * @brief   Lichao SegTree + Divide and Conquer By SegTree
 * @date    2023-10-27
 */
#include <climits>
#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50, S = -1e9, T = 1e9;
constexpr i64 inf = 4e18;
int n;
// --- 李超线段树 ---
struct Line {
  i64 k, b;
  i64 operator()(const i64 &val) const { return k * val + b; }
} line[N];
struct SegTree {
  struct Node {
    int id, lc, rc;
  } tree[N << 5];
  int cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void modify(int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    if (!tree[u].id) return tree[u].id = val, void();
    int &cur = tree[u].id, mid = (s + t) >> 1;
    if (line[val](mid) > line[cur](mid)) std::swap(val, cur);
    if (line[val](s) > line[cur](s)) modify(s, mid, lc(u), val);
    if (line[val](t) > line[cur](t)) modify(mid + 1, t, rc(u), val);
  }
  i64 query(int tar, int s, int t, int u) {
    if (!u) return -inf;
    if (s == t) return line[tree[u].id](tar);
    int mid = (s + t) >> 1;
    i64 res = line[tree[u].id](tar);
    if (mid >= tar) return std::max(res, query(tar, s, mid, lc(u)));
    else return std::max(res, query(tar, mid + 1, t, rc(u)));
  }
} seg;
int rt[N << 2], pos[N];
// ------------------
// --- 线段树分治 ---
int lc(int u) { return u << 1; }
int rc(int u) { return u << 1 | 1; }
void build(int s, int t, int u) {
  if (s == t) return pos[s] = u, void();
  int mid = (s + t) >> 1;
  build(s, mid, lc(u)), build(mid + 1, t, rc(u));
}
void modify(int l, int r, int s, int t, int u, int val) {
  if (l <= s && t <= r) return seg.modify(S, T, rt[u], val);
  int mid = (s + t) >> 1;
  if (mid >= l) modify(l, r, s, mid, lc(u), val);
  if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
}
// ------------------
int opt[N], l[N], r[N], val[N];
void solve() {
  std::cin >> n, build(1, n, 1);
  for (int i = 1, k, b, u; i <= n; i++) {
    std::cin >> opt[i];
    if (opt[i] == 1) std::cin >> k >> b, line[i] = {k, b}, l[i] = i, r[i] = n;
    else if (opt[i] == 2) std::cin >> u, r[u] = i;
    else std::cin >> val[i];
  }
  for (int i = 1; i <= n; i++) {
    if (opt[i] == 1) modify(l[i], r[i], 1, n, 1, i);
  }
  for (int i = 1; i <= n; i++) {
    if (opt[i] != 3) continue;
    i64 res = -inf;
    for (int p = pos[i]; p; p >>= 1) {
      res = std::max(res, seg.query(val[i], S, T, rt[p]));
    }
    if (res == -inf) std::cout << "EMPTY SET\n";
    else std::cout << res << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
