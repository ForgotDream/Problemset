/**
 * @file    P2042 [NOI2005] 维护数列.cpp
 * @author  ForgotDream
 * @brief   FHQ
 * @date    2023-12-06
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 5e5 + 50;
int n, m;
struct FHQ {
  struct Node {
    int lc, rc, prm, siz;
    i64 val, sum, ass = -1e9;
    bool rev;
    i64 lmax, rmax, max;
  } tree[N];
  int cnt, rt;
  std::random_device rd;
  std::mt19937 rng;
  std::stack<int> s;
  FHQ() { rng = std::mt19937(rd()); }
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  int init(i64 val) {
    int u;
    if (!s.empty()) u = s.top(), s.pop();
    else u = ++cnt;
    lc(u) = rc(u) = 0, tree[u].prm = rng(), tree[u].siz = 1;
    tree[u].val = tree[u].sum = val, tree[u].ass = -1e9;
    tree[u].lmax = tree[u].rmax = std::max(0l, val);
    tree[u].max = val;
    tree[u].rev = false;
    return u;
  }
  void pushup(int u) {
    if (!u) return;
    tree[u].siz = tree[lc(u)].siz + tree[rc(u)].siz + 1;
    tree[u].sum = tree[lc(u)].sum + tree[u].val + tree[rc(u)].sum;
    tree[u].lmax = std::max({tree[lc(u)].lmax, tree[lc(u)].sum + tree[u].val + tree[rc(u)].lmax, 0l});
    tree[u].rmax = std::max({tree[lc(u)].rmax + tree[u].val + tree[rc(u)].sum, tree[rc(u)].rmax, 0l});
    tree[u].max = std::max(tree[lc(u)].rmax + tree[rc(u)].lmax, 0l) + tree[u].val;
    if (lc(u)) tree[u].max = std::max(tree[lc(u)].max, tree[u].max);
    if (rc(u)) tree[u].max = std::max(tree[rc(u)].max, tree[u].max);
  }
  void pushdown(int u) {
    if (tree[u].ass != -1e9) {
      if (lc(u)) assTagging(lc(u), tree[u].ass);
      if (rc(u)) assTagging(rc(u), tree[u].ass);
      tree[u].ass = -1e9;
    }
    if (tree[u].rev) {
      if (lc(u)) revTagging(lc(u));
      if (rc(u)) revTagging(rc(u));
      tree[u].rev = false;
    }
  }
  void assTagging(int u, i64 val) {
    tree[u].ass = tree[u].val = val, tree[u].sum = tree[u].siz * val;
    tree[u].lmax = tree[u].rmax = std::max(0l, tree[u].sum);
    tree[u].max = std::max(val, tree[u].sum);
  }
  void revTagging(int u) {
    tree[u].rev ^= 1;
    std::swap(lc(u), rc(u)), std::swap(tree[u].lmax, tree[u].rmax);
  }
  void split(int u, int idx, int &l, int &r) {
    if (!u) return l = r = 0, void();
    pushdown(u);
    if (tree[lc(u)].siz < idx) l = u, split(rc(u), idx - tree[lc(u)].siz - 1, rc(u), r);
    else r = u, split(lc(u), idx, l, lc(u));
    pushup(u);
  }
  int merge(int l, int r) {
    if (!l || !r) return l + r;
    if (tree[l].prm > tree[r].prm) return pushdown(l), rc(l) = merge(rc(l), r), pushup(l), l;
    else return pushdown(r), lc(r) = merge(l, lc(r)), pushup(r), r;
  }
  void recycle(int u) {
    if (!u) return;
    recycle(lc(u)), recycle(rc(u));
    s.push(u);
  }
  void erase(int l, int r) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    recycle(p1);
    rt = merge(p0, p2);
  }
  void assign(int l, int r, i64 val) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    assTagging(p1, val);
    rt = merge(p0, merge(p1, p2));
  }
  void reverse(int l, int r) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    revTagging(p1);
    rt = merge(p0, merge(p1, p2));
  }
  i64 sum(int l, int r) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    // std::cerr << p0 << " " << p1 << " " << p2 << "\n";
    i64 res = tree[p1].sum;
    // std::cerr << l << " " << r << " " << traverse(p1) << "\n";
    rt = merge(p0, merge(p1, p2));
    return res;
  }
  i64 subsum() { return tree[rt].max; }
  // i64 subsum() { return std::cerr << "\n", tree[rt].max; }
  void insert(int pos, const std::vector<i64> &l) {
    if (l.empty()) return;
    int p0, p2;
    split(rt, pos, p0, p2);
    int p1 = init(*l.begin());
    auto it = l.begin() + 1;
    while (it != l.end()) p1 = merge(p1, init(*it++));
    rt = merge(p0, merge(p1, p2));
  }
  std::string traverse(int u) {
    if (!u) return "0";
    return "[" + traverse(lc(u)) + ", " + std::to_string(u) + ", " + traverse(rc(u)) + "]";
  }
} fhq;
void solve() {
  std::cin >> n >> m;
  for (int i = 1, v; i <= n; i++) std::cin >> v, fhq.rt = fhq.merge(fhq.rt, fhq.init(v));
  int tmp = 0;
  for (int p, t, v; m; m--) {
    static char s[20];
    std::cin >> s;
    if (s[0] == 'I') {
      std::cin >> p >> t;
      std::vector<i64> l;
      while (t--) std::cin >> v, l.push_back(v);
      fhq.insert(p, l);
    } else if (s[0] == 'D') {
      std::cin >> p >> t;
      fhq.erase(p, p + t - 1);
    } else if (s[0] == 'R') {
      std::cin >> p >> t;
      fhq.reverse(p, p + t - 1);
    } else if (s[0] == 'G') {
      std::cin >> p >> t;
      tmp++;
      if (tmp == 41) std::cerr << s << " " << p << " " << t << "\n";
      std::cout << fhq.sum(p, p + t - 1) << "\n";
    } else if (s[2] == 'K') {
      std::cin >> p >> t >> v;
      fhq.assign(p, p + t - 1, v);
    } else {
      tmp++;
      if (tmp == 41) std::cerr << s << "\n";
      std::cout << fhq.subsum() << "\n";
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
