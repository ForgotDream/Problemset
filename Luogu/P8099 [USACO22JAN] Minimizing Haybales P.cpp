/**
 * @file    P8099 [USACO22JAN] Minimizing Haybales P.cpp
 * @author  ForgotDream
 * @brief   BST
 * @date    2023-08-04
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
int n, k, h[N];
template<int N = 300050>
struct FHQTreap {
  std::mt19937 rnd;
  std::random_device rd;
  struct Node {
    int lc = 0, rc = 0;
    int max = 0, min = 0, val = 0, siz = 0, prm;
  } t[N];
  int cnt = 0, rt = 0;
  FHQTreap() { rnd = std::mt19937(rd()), t[rt].min = 2e9, t[rt].max = 0; }
  int &lc(int u) { return t[u].lc; }
  int &rc(int u) { return t[u].rc; }
  void pushup(int u) {
    t[u].siz = t[lc(u)].siz + t[rc(u)].siz + 1;
    t[u].max = std::max({t[u].val, t[lc(u)].max, t[rc(u)].max});
    t[u].min = std::min({t[u].val, t[lc(u)].min, t[rc(u)].min});
  }
  int init(int val) {
    cnt++;
    t[cnt].val = t[cnt].max = t[cnt].min = val;
    t[cnt].prm = rnd(), t[cnt].siz = 1;
    return cnt;
  }
  void split(int u, int val, int &l, int &r) {
    if (!u) return void(l = r = 0);
    if (t[lc(u)].siz < val) l = u, split(rc(u), val - t[lc(u)].siz - 1, rc(u), r);
    else r = u, split(lc(u), val, l, lc(u));
    pushup(u);
  }
  int merge(int l, int r) {
    if (!l || !r) return l + r;
    if (t[l].prm > t[r].prm) return rc(l) = merge(rc(l), r), pushup(l), l;
    else return lc(r) = merge(l, lc(r)), pushup(r), r;
  }
  int find1(int u, int val) {
    int res = 0;
    while (u) {
      if (std::min(t[u].val, t[rc(u)].min) < val - k || 
          std::max(t[u].val, t[rc(u)].max) > val + k) {
        res += t[lc(u)].siz + 1, u = rc(u);
      } else {
        u = lc(u);
      }
    }
    return res;
  }
  int find2(int u, int val) {
    int res = 0;
    while (u) {
      if (std::max(t[u].val, t[lc(u)].max) > val) u = lc(u);
      else res += t[lc(u)].siz + 1, u = rc(u);
    }
    return res;
  }
  void traverse(int u) {
    if (!u) return;
    traverse(lc(u));
    std::cout << t[u].val << "\n";
    traverse(rc(u));
  }
};
FHQTreap fhq;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> h[i];
  for (int i = 1, l, r, p; i <= n; i++) {
    fhq.split(fhq.rt, fhq.find1(fhq.rt, h[i]), l, r);
    fhq.split(r, fhq.find2(r, h[i]), r, p);
    fhq.rt = fhq.merge(fhq.merge(l, r), fhq.merge(fhq.init(h[i]), p));
  }
  fhq.traverse(fhq.rt);
  return 0;
}