/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-14
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, k = 1e5, a[N];
int pre[N];
struct SegTree {
  struct Node {
    int lc, rc, sum, rt;
  } tree[N << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline int clone(int u) {
    tree[++cnt] = tree[u];
    return cnt;
  }
  inline void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
};
struct SegTree2 : SegTree {
  void modify(int tar, int s, int t, int &u, int v) {
    u = clone(v);
    if (s == t) return tree[u].sum++, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), lc(v));
    else modify(tar, mid + 1, t, rc(u), rc(v));
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u, int v) {
    if (l <= s && t <= r) return tree[u].sum - tree[v].sum;
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u), lc(v));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u), rc(v));
    return res;
  }
} s2;
struct SegTree1 : SegTree {
  void modify(int tar, int s, int t, int &u, int v, int val) {
    u = clone(v);
    if (s == t) {
      tree[u].sum++;
      std::cerr << tar << " " << val << "\n";
      s2.modify(val, 0, n, tree[u].rt, tree[v].rt);
      return;
    }
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), lc(v), val);
    else modify(tar, mid + 1, t, rc(u), rc(v), val);
    pushup(u);
  }
  int querySum(int l, int r, int s, int t, int u, int v) {
    if (l <= s && t <= r) return tree[u].sum - tree[v].sum;
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += querySum(l, r, s, mid, lc(u), lc(v));
    if (mid < r) res += querySum(l, r, mid + 1, t, rc(u), rc(v));
    return res;
  }
  int queryCnt(int l, int r, int s, int t, int u, int v, int ll, int rr) {
    if (l <= s && t <= r) return s2.query(ll, rr, 0, n, tree[u].rt, tree[v].rt);
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += queryCnt(l, r, s, mid, lc(u), lc(v), ll, rr);
    if (mid < r) res += queryCnt(l, r, mid + 1, t, rc(u), rc(v), ll, rr);
    return res;
  }
} s1;
int rt[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    s1.modify(a[i], 1, k, rt[i], rt[i - 1], pre[a[i]]);
    pre[a[i]] = i;
  }
  for (int l, r, a, b; m; m--) {
    std::cin >> l >> r >> a >> b;
    std::cout << s1.querySum(a, b, 1, k, rt[r], rt[l - 1]) << " "
              << s1.queryCnt(a, b, 1, k, rt[r], rt[l - 1], 0, l - 1) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
