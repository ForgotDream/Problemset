/*
 * @file    P4396 [AHOI2013] 作业.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-22
 */
#include <bits/stdc++.h>

using i64 = long long;

// 普通的数颜色的话，强制在线可以 n log^2 n 树套树
// 离线的话就可以 n log n 了
// 这题还多了一维，因此肯定要多带个 log，所以考虑离线做法
// 思路貌似还挺清晰的？
// 希望高贵 polylog 做法不要被傻逼 sqrt 吊打了

constexpr int N = 1e5 + 50;
int n, q, a[N], pre[N];

struct InnerSegTree {
  static constexpr int M = 1e7 + 10;
  int lc[M], rc[M], col[M];
  int cnt;
  inline void pushup(int u) { col[u] = col[lc[u]] + col[rc[u]]; }
  void modify(int tar, int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    if (s == t) return col[u] += val, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc[u], val);
    else modify(tar, mid + 1, t, rc[u], val);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (!u) return 0;
    if (l <= s && t <= r) return col[u];
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc[u]);
    if (mid < r) res += query(l, r, mid + 1, t, rc[u]);
    return res;
  }
} s1;

struct OutterBIT {
  int rt[N];
  inline void modify(int u, int pos, int val) {
    for (int i = u; i <= 1e5; i += i & -i) {
      s1.modify(pos, 1, n, rt[i], val);
    }
  }
  inline int query(int u, int l, int r) {
    int res = 0;
    for (int i = u; i; i -= i & -i) {
      res += s1.query(l, r, 1, n, rt[i]);
    }
    return res;
  }
  inline int query(int s, int t, int l, int r) {
    return query(t, l, r) - query(s - 1, l, r);
  }
} s2;

struct ShabiTree {
  static constexpr int M = N * 20;
  int lc[M], rc[M], sum[M];
  int cnt;
  inline void pushup(int u) { sum[u] = sum[lc[u]] + sum[rc[u]]; }
  inline int clone(int u) {
    ++cnt;
    std::tie(lc[cnt], rc[cnt], sum[cnt]) = std::tie(lc[u], rc[u], sum[u]);
    return cnt;
  }
  void modify(int tar, int s, int t, int &u, int v) {
    u = clone(v);
    if (s == t) return sum[u]++, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc[u], lc[v]);
    else modify(tar, mid + 1, t, rc[u], rc[v]);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u, int v) {
    if (l <= s && t <= r) return sum[u] - sum[v];
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc[u], lc[v]);
    if (mid < r) res += query(l, r, mid + 1, t, rc[u], rc[v]);
    return res;
  }
} s3;
int rt[N];

struct Query {
  int l, r, s, t, idx;
  bool operator<(const Query &rhs) const {
    return r < rhs.r;
  }
} qry[N];
int ansCol[N], ansCnt[N];

void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    s3.modify(a[i], 1, 1e5, rt[i], rt[i - 1]);
  }

  for (int i = 1; i <= q; i++) {
    std::cin >> qry[i].l >> qry[i].r >> qry[i].s >> qry[i].t;
    qry[i].idx = i;
  }

  std::sort(qry + 1, qry + q + 1);
  int p = 1;
  for (int i = 1; i <= q; i++) {
    auto [l, r, s, t, idx] = qry[i];
    for (int j = p; j <= r; j++) {
      if (pre[a[j]]) s2.modify(a[j], pre[a[j]], -1);
      s2.modify(a[j], j, 1), pre[a[j]] = j;
    }
    ansCol[idx] = s2.query(s, t, l, r);
    ansCnt[idx] = s3.query(s, t, 1, 1e5, rt[r], rt[l - 1]);
    p = r + 1;
  }

  for (int i = 1; i <= q; i++) std::cout << ansCnt[i] << " " << ansCol[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
