#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
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
  int rnk2(int u, i64 val) {
    if (!u) return 0;
    pushdown(u);
    if (tree[u].val < val) return tree[lc(u)].siz + 1 + rnk2(rc(u), val);
    else return rnk2(lc(u), val);
  }
} fhq;
std::vector<int> a = {1, 2, 5, 8, 6};
void solve() {
  for (auto i : a) fhq.insert(i);
  std::cerr << fhq.rnk1(fhq.rt, 5) << " " << fhq.rnk2(fhq.rt, 5) << "\n";
  fhq.tagging(fhq.rt, 1);
  std::cerr << fhq.rnk1(fhq.rt, 5) << " " << fhq.rnk2(fhq.rt, 5) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
