/*
 * @file    P3380 【模板】二逼平衡树（树套树）.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-17
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, q, m, a[N];
struct InnerSegTree {
  struct Node {
    int lc, rc, sum;
  } tree[N << 8];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  void modify(int tar, int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    if (s == t) return tree[u].sum += val, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (!u) return 0;
    if (l <= s && t <= r) return tree[u].sum;
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u));
    return res;
  }
} s1;
struct OutterSegTree {
  int rt[N << 2];
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  void modify(int tar, int s, int t, int u, int pos, int val) {
    s1.modify(pos, 1, n, rt[u], val);
    if (s == t) return;
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), pos, val);
    else modify(tar, mid + 1, t, rc(u), pos, val);
  }
  int kth(int s, int t, int u, int ll, int rr, int k) {
    if (s == t) return s;
    int mid = (s + t) >> 1, cur = s1.query(ll, rr, 1, n, rt[lc(u)]);
    if (cur >= k) return kth(s, mid, lc(u), ll, rr, k);
    else return kth(mid + 1, t, rc(u), ll, rr, k - cur);
  }
  int query(int l, int r, int s, int t, int u, int ll, int rr) {
    if (l <= s && t <= r) return s1.query(ll, rr, 1, n, rt[u]);
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u), ll, rr);
    if (mid < r) res += query(l, r, mid + 1, t, rc(u), ll, rr);
    return res;
  }
  int pre(int s, int t, int u, int ll, int rr) {
    if (s == t) return s1.query(ll, rr, 1, n, rt[u]) ? s : 0;
    int mid = (s + t) >> 1;
    if (s1.query(ll, rr, 1, n, rt[rc(u)])) return pre(mid + 1, t, rc(u), ll, rr); 
    else return pre(s, mid, lc(u), ll, rr);
  }
  int pre(int l, int r, int s, int t, int u, int ll, int rr) {
    if (l > r) return 0;
    if (l <= s && t <= r) return pre(s, t, u, ll, rr);
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res = std::max(res, pre(l, r, s, mid, lc(u), ll, rr));
    if (mid < r) res = std::max(res, pre(l, r, mid + 1, t, rc(u), ll, rr));
    return res;
  }
  int suf(int s, int t, int u, int ll, int rr) {
    if (s == t) return s1.query(ll, rr, 1, n, rt[u]) ? s : 1e9;
    int mid = (s + t) >> 1;
    if (s1.query(ll, rr, 1, n, rt[lc(u)])) return suf(s, mid, lc(u), ll, rr);
    else return suf(mid + 1, t, rc(u), ll, rr);
  }
  int suf(int l, int r, int s, int t, int u, int ll, int rr) {
    if (l > r) return 1e9;
    if (l <= s && t <= r) return suf(s, t, u, ll, rr);
    int mid = (s + t) >> 1, res = 1e9;
    if (mid >= l) res = std::min(res, suf(l, r, s, mid, lc(u), ll, rr));
    if (mid < r) res = std::min(res, suf(l, r, mid + 1, t, rc(u), ll, rr));
    return res;
  }
} s2;
struct Query { int opt, l, r, v; };
std::vector<Query> qry;
std::vector<int> b;
inline int find(int u) { 
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
void solve() {
  std::cin >> n >> q;
  b = {-2147483647, 2147483647};
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]);
  qry.resize(q);
  for (auto &[opt, l, r, v] : qry) {
    std::cin >> opt;
    if (opt == 3) std::cin >> l >> v;
    else std::cin >> l >> r >> v;
    if (opt != 2) b.push_back(v);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  m = b.size();
  for (int i = 1; i <= n; i++) s2.modify(find(a[i]), 1, m, 1, i, 1);
  for (auto &[opt, l, r, v] : qry) {
    if (opt == 1) {
      std::cout << s2.query(1, find(v) - 1, 1, m, 1, l, r) + 1 << "\n";
    } else if (opt == 2) {
      std::cout << b[s2.kth(1, m, 1, l, r, v) - 1] << "\n";
    } else if (opt == 3) {
      s2.modify(find(a[l]), 1, m, 1, l, -1);
      a[l] = v;
      s2.modify(find(a[l]), 1, m, 1, l, 1);
    } else if (opt == 4) {
      int ans = s2.pre(1, find(v) - 1, 1, m, 1, l, r);
      if (ans == 0) std::cout << -2147483647 << "\n";
      else std::cout << b[ans - 1] << "\n";
    } else {
      int ans = s2.suf(find(v) + 1, m, 1, m, 1, l, r);
      if (ans == 1e9) std::cout << 2147483647 << "\n";
      else std::cout << b[ans - 1] << "\n";
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
