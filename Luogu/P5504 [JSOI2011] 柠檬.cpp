/*
 * @file    P5504 [JSOI2011] 柠檬.cpp
 * @author  ForgotDream
 * @brief   Lichao Segment Tree + DP
 * @date    2024-01-03
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 1e4 + 50;
int n, a[N];
int cnt[N], cur[N];

struct Line {
  i64 k, b;
  i64 operator()(i64 x) { return k * x + b; }
} line[N];

struct SegTree {
  struct Node {
    int lc, rc, idx;
  } tree[M << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  void modify(int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    int mid = (s + t) >> 1, &cur = tree[u].idx;
    if (!cur) return cur = val, void();
    if (line[val](mid) > line[cur](mid)) std::swap(val, cur);
    if (line[val](s) > line[cur](s)) modify(s, mid, lc(u), val);
    if (line[val](t) > line[cur](t)) modify(mid + 1, t, rc(u), val);
  }
  i64 query(int tar, int s, int t, int u) {
    if (!u) return 0;
    if (s == t) return line[tree[u].idx](tar);
    int mid = (s + t) >> 1;
    i64 res = line[tree[u].idx](tar);
    if (mid >= tar) return std::max(res, query(tar, s, mid, lc(u)));
    else return std::max(res, query(tar, mid + 1, t, rc(u)));
  }
} seg;
int rt[M];

i64 f[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], cnt[a[i]]++;

  for (int i = 1; i <= n; i++) {
    cur[a[i]]++;
    i64 p = cur[a[i]];
    line[i] = {-2 * a[i] * (p - 1), a[i] * (p - 1) * (p - 1) + f[i - 1]};
    seg.modify(1, cnt[a[i]], rt[a[i]], i);
    f[i] = a[i] * p * p + seg.query(p, 1, cnt[a[i]], rt[a[i]]);
  }
  std::cout << f[n] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
