/**
 * @file    P4036 [JSOI2008] 火星人.cpp
 * @author  ForgotDream
 * @brief   Hash + FHQ
 * @date    2023-12-06
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;

constexpr int N = 2e5 + 50;
constexpr u64 base = 2333;
std::string s;
int n, m;
u64 pw[N];
struct FHQ {
  struct Node {
    int lc, rc, prm, siz;
    u64 val, sum;
  } tree[N];
  int cnt, rt;
  std::random_device rd;
  std::mt19937 rng;
  FHQ() { rng = std::mt19937(rd()); }
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void pushup(int u) {
    tree[u].siz = tree[lc(u)].siz + tree[rc(u)].siz + 1;
    tree[u].sum = tree[lc(u)].sum * pw[tree[rc(u)].siz + 1] + 
                  tree[u].val * pw[tree[rc(u)].siz] + tree[rc(u)].sum;
  }
  int init(u64 val) {
    cnt++, lc(cnt) = rc(cnt) = 0, tree[cnt].siz = 1;
    tree[cnt].prm = rng(), tree[cnt].val = tree[cnt].sum = val;
    return cnt;
  }
  void split(int u, int idx, int &l, int &r) {
    if (!u) return l = r = 0, void();
    if (tree[lc(u)].siz >= idx) r = u, split(lc(u), idx, l, lc(u));
    else l = u, split(rc(u), idx - tree[lc(u)].siz - 1, rc(u), r);
    // if (tree[lc(u)].siz < idx) l = u, split(rc(u), idx - tree[lc(u)].siz - 1, rc(u), r);
    // else r = u, split(lc(u), idx, l, lc(u));
    pushup(u);
  }
  int merge(int l, int r) {
    if (!l || !r) return l + r;
    if (tree[l].prm > tree[r].prm) return rc(l) = merge(rc(l), r), pushup(l), l;
    else return lc(r) = merge(l, lc(r)), pushup(r), r;
  }
  std::string traverse(int u) {
    if (!u) return "0";
    return "[" + traverse(lc(u)) + ", " + std::to_string(u) + ", " + traverse(rc(u)) + "]";
  }
  u64 hash(int l, int r) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    u64 res = tree[p1].sum;
    rt = merge(p0, merge(p1, p2));
    return res;
  }
  void insert(int pos, u64 val) {
    int p0, p1, p2;
    p1 = init(val), split(rt, pos, p0, p2);
    rt = merge(p0, merge(p1, p2));
  }
  void modify(int pos, u64 val) {
    int p0, p1, p2;
    split(rt, pos, p1, p2);
    split(p1, pos - 1, p0, p1);
    tree[p1].val = tree[p1].sum = val;
    rt = merge(p0, merge(p1, p2));
  }
} fhq;
void init() {
  pw[0] = 1;
  for (int i = 1; i <= 1e5; i++) pw[i] = pw[i - 1] * base;
}
void solve() {
  init();
  std::cin >> s >> m;
  n = s.length();
  for (auto c : s) fhq.rt = fhq.merge(fhq.rt, fhq.init(c));
  for (int i = 0; i < m; i++) {
    char opt;
    std::cin >> opt;
    if (opt == 'Q') {
      int x, y;
      std::cin >> x >> y;
      if (x > y) std::swap(x, y);
      int lo = 1, hi = n - y + 1, ans = 0;
      while (lo <= hi) {
        auto check = [&](int u) -> bool {
          return fhq.hash(x, x + u - 1) == fhq.hash(y, y + u - 1);
        };
        int mid = (lo + hi) >> 1;
        if (check(mid)) lo = mid + 1, ans = mid;
        else hi = mid - 1;
      }
      std::cout << ans << "\n";
    } else if (opt == 'R') {
      int x;
      char d;
      std::cin >> x >> d;
      fhq.modify(x, d);
    } else {
      int x;
      char d;
      std::cin >> x >> d;
      fhq.insert(x, d), ++n;
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
