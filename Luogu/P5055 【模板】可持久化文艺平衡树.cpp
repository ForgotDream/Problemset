/**
 * @file    P5055 【模板】可持久化文艺平衡树.cpp
 * @author  ForgotDream
 * @brief   FHQ
 * @date    2023-12-17
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
struct FHQ {
  std::random_device rd;
  std::mt19937 rng;
  struct Node {
    int lc, rc, siz, prm;
    i64 val, sum;
    bool tag;
  } tree[N << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) {
    tree[u].siz = tree[lc(u)].siz + tree[rc(u)].siz + 1;
    tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum + tree[u].val;
  }
  inline void pushdown(int u) {
    if (!tree[u].tag) return;
    std::swap(lc(u), rc(u));
    if (lc(u)) lc(u) = clone(lc(u)), tree[lc(u)].tag ^= true;
    if (rc(u)) rc(u) = clone(rc(u)), tree[rc(u)].tag ^= true;
    tree[u].tag = false;
  }
  inline int init(i64 val) {
    ++cnt, lc(cnt) = rc(cnt) = 0, tree[cnt].siz = 1, tree[cnt].prm = rng();
    tree[cnt].val = tree[cnt].sum = val, tree[cnt].tag = false;
    return cnt;
  }
  inline int clone(int u) { return tree[++cnt] = tree[u], cnt; }
  void split(int u, int idx, int &l, int &r) {
    if (!u) return l = r = 0, void();
    pushdown(u);
    if (tree[lc(u)].siz < idx) {
      l = clone(u), split(rc(l), idx - tree[lc(u)].siz - 1, rc(l), r);
      pushup(l);
    } else {
      r = clone(u), split(lc(r), idx, l, lc(r));
      pushup(r);
    }
  }
  int merge(int l, int r) {
    if (!l || !r) return l + r;
    if (tree[l].prm > tree[r].prm) return pushdown(l), rc(l) = merge(rc(l), r), pushup(l), l;
    else return pushdown(r), lc(r) = merge(l, lc(r)), pushup(r), r;
  }
  inline void insert(int &u, int idx, i64 val) {
    int p0, p1;
    split(u, idx, p0, p1);
    u = merge(p0, merge(init(val), p1));
  }
  inline void erase(int &u, int idx) {
    int p0, p1, p2;
    split(u, idx, p0, p2), split(p0, idx - 1, p0, p1);
    u = merge(p0, p2);
  }
  inline void reverse(int &u, int l, int r) {
    int p0, p1, p2;
    split(u, r, p0, p2), split(p0, l - 1, p0, p1);
    tree[p1].tag ^= true;
    u = merge(p0, merge(p1, p2));
  }
  inline i64 query(int &u, int l, int r) {
    int p0, p1, p2;
    split(u, r, p0, p2), split(p0, l - 1, p0, p1);
    i64 res = tree[p1].sum;
    u = merge(p0, merge(p1, p2));
    return res;
  }
} fhq;
int rt[N], n;
void solve() {
  std::cin >> n;
  i64 lst = 0;
  for (i64 i = 1, v, opt, l, r, p, x; i <= n; i++) {
    std::cin >> v >> opt;
    rt[i] = rt[v];
    if (opt == 1) {
      std::cin >> p >> x, p ^= lst, x ^= lst;
      fhq.insert(rt[i], p, x);
    } else if (opt == 2) {
      std::cin >> p, p ^= lst;
      fhq.erase(rt[i], p);
    } else if (opt == 3) {
      std::cin >> l >> r, l ^= lst, r ^= lst;
      fhq.reverse(rt[i], l, r);
    } else {
      std::cin >> l >> r, l ^= lst, r ^= lst;
      std::cout << (lst = fhq.query(rt[i], l, r)) << "\n";
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
