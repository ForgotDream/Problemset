/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-15
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e5 + 50;
i64 n, k, m, c, d, a[N];
struct FHQ {
  std::random_device rd;
  std::mt19937 rng;
  struct Node {
    int lc, rc, prm, siz;
    i64 val, sum, tag;
  } tree[N];
  int cnt, rt;
  FHQ() { rng = std::mt19937(rd()); }
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) {
    tree[u].siz = tree[lc(u)].siz + tree[rc(u)].siz + 1;
    tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum + tree[u].val;
  }
  inline void pushdown(int u) {
    if (!tree[u].tag) return;
    if (lc(u)) tagging(lc(u), tree[u].tag);
    if (rc(u)) tagging(rc(u), tree[u].tag);
    tree[u].tag = 0;
  }
  inline void tagging(int u, int val) {
    tree[u].sum += tree[u].siz * val;
    tree[u].val += val, tree[u].tag += val;
  }
  inline int init(i64 val) {
    cnt++, lc(cnt) = rc(cnt) = 0, tree[cnt].prm = rng(), tree[cnt].siz = 1;
    tree[cnt].val = tree[cnt].sum = val, tree[cnt].tag = 0;
    return cnt;
  }
  void split(int u, i64 val, int &l, int &r) {
    if (!u) return l = r = 0, void();
    pushdown(u);
    if (tree[u].val <= val) l = u, split(rc(u), val, rc(u), r);
    else r = u, split(lc(u), val, l, lc(u));
    pushup(u);
  }
  int merge(int l, int r) {
    if (!l || !r) return l + r;
    if (tree[l].prm > tree[r].prm) return pushdown(l), rc(l) = merge(rc(l), r), pushup(l), l;
    else return pushdown(r), lc(r) = merge(l, lc(r)), pushup(r), r;
  }
  void insert(i64 val) {
    int p0, p1;
    split(rt, val, p0, p1);
    rt = merge(p0, merge(init(val), p1));
  }
  void erase(i64 val) {
    int p0, p1, p2;
    split(rt, val, p0, p2);
    split(p0, val - 1, p0, p1);
    p1 = merge(lc(p1), rc(p1));
    rt = merge(p0, merge(p1, p2));
  }
  int rnk1(int u, i64 val) {
    if (!u) return 0;
    pushdown(u);
    if (tree[u].val <= val) return tree[lc(u)].siz + 1 + rnk1(rc(u), val);
    else return rnk1(lc(u), val);
  }
  void traverse(int u) {
    if (!u) return;
    pushdown(u);
    traverse(lc(u)), std::cerr << tree[u].val << " ", traverse(rc(u));
  }
} t1, t2;
int check1(i64 u) {
  int k1 = t1.rnk1(t1.rt, u), k2 = t2.rnk1(t2.rt, u);
  return k1 + k2;
}
i64 chk() {
  i64 lo = 0, hi = 1e15, res = 0;
  while (lo <= hi) {
    i64 mid = (lo + hi) >> 1;
    if (check1(mid) >= k) {
      hi = mid - 1;
      res = mid;
    } else {
      lo = mid + 1;
    }
  }
  return res;
}
void solve() {
  std::cin >> n >> k >> m >> c >> d;
  k = n - k + 1;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) t1.insert(a[i] + c + (i - 1) * d);
  for (int i = m + 1; i <= n; i++) t2.insert(a[i]);
  i64 ans = chk();
  for (int i = m + 1; i <= n; i++) {
    t1.erase(a[i - m] + c), t2.insert(a[i - m]);
    t1.insert(a[i] + c + m * d), t2.erase(a[i]);
    t1.tagging(t1.rt, -d);
    // std::cerr << chk() << "\n";
    // std::cerr << check1(35) << " " << check2(35) << " " << k << "\n";
    // t1.traverse(t1.rt), t2.traverse(t2.rt), std::cerr << "\n";
    ans = std::max(ans, chk());
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
