/**
 * @file    P8868 [NOIP2022] 比赛.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-11-13
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using pii = std::pair<int, int>;

constexpr int N = 2.5e5 + 50;
int n, q;
u64 a[N], b[N];
std::vector<pii> qry[N];
struct SegTree {/*{{{*/
  struct Info {
    u64 sab, sa, sb, sh, len;
    Info() { sab = sa = sb = sh = len = 0; }
    Info(u64 sab, u64 sa, u64 sb, u64 sh, u64 len)
        : sab(sab), sa(sa), sb(sb), sh(sh), len(len) {}
    friend Info operator+(const Info &lhs, const Info &rhs) {
      return Info(lhs.sab + rhs.sab, lhs.sa + rhs.sa, lhs.sb + rhs.sb,
                  lhs.sh + rhs.sh, lhs.len + rhs.len);
    }
  } info[N << 2];
  struct Tag {
    // The priority of add is greater than assign(cover).
    u64 ca, cb,           // c stands for cover
        da, db, dab, dh;  // d stands for delta(the change value)
    Tag() { clear(); }
    void clear() { ca = cb = da = db = dab = dh = 0; }
    bool valid() { return ca || cb || da || db || dab || dh; }
    Tag(u64 ca, u64 cb, u64 da, u64 db, u64 dab, u64 dh)
        : ca(ca), cb(cb), da(da), db(db), dab(dab), dh(dh) {}
    // assume that `rhs` is applied earlier than `lhs`
    friend Tag operator+(const Tag &lhs, const Tag &rhs) {
      Tag res = rhs;
      if (rhs.ca && rhs.cb) {
        res.dh += lhs.dab * rhs.ca * rhs.cb + 
                  lhs.da * rhs.ca + lhs.db * rhs.cb + lhs.dh;
      } else if (rhs.ca) {
        res.db += lhs.dab * rhs.ca + lhs.db;
        res.dh += lhs.dh + lhs.da * rhs.ca;
      } else if (rhs.cb) {
        res.da += lhs.dab * rhs.cb + lhs.da;
        res.dh += lhs.dh + lhs.db * rhs.cb;
      } else {
        res.da += lhs.da, res.db += lhs.db, res.dab += lhs.dab;
        res.dh += lhs.dh;
      }
      if (lhs.ca) res.ca = lhs.ca;
      if (lhs.cb) res.cb = lhs.cb;
      return res;
    }
  } tag[N << 2];
  Info apply(const Info &info, const Tag &tag) {
    Info res = info;
    // add > assign
    res.sh += tag.dab * info.sab + tag.db * info.sb + tag.da * info.sa + 
              tag.dh * info.len;
    if (tag.ca && tag.cb) {
      res.sab = info.len * tag.ca * tag.cb;
      res.sa = info.len * tag.ca;
      res.sb = info.len * tag.cb;
    } else if (tag.ca) {
      res.sab = info.sb * tag.ca;
      res.sa = info.len * tag.ca;
    } else if (tag.cb) {
      res.sab = info.sa * tag.cb;
      res.sb = info.len * tag.cb;
    } else {
      /* nothing will be done... */
    }
    return res;
  }
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { info[u] = info[lc(u)] + info[rc(u)]; }
  void pushdown(int u) {
    if (tag[u].valid()) {
      tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
      tag[u].clear();
    }
  }
  void tagging(int u, const Tag &val) { 
    tag[u] = val + tag[u], info[u] = apply(info[u], val); 
  }
  void build(int s, int t, int u) {
    info[u].len = t - s + 1;
    if (s == t) return;
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
  }
  void modify(int l, int r, int s, int t, int u, const Tag &val) {
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  Info query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return info[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= r) return query(l, r, s, mid, lc(u));
    else if (mid < l) return query(l, r, mid + 1, t, rc(u));
    else return query(l, r, s, mid, lc(u)) + query(l, r, mid + 1, t, rc(u));
  }
} seg;/*}}}*/
std::stack<int, std::vector<int>> sa, sb;
u64 ans[N];
void solve() {
  std::cin >> *(new int) >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  seg.build(1, n, 1);
  std::cin >> q;
  for (int i = 1, l, r; i <= q; i++) {
    std::cin >> l >> r;
    qry[r].emplace_back(l, i);
  }
  sa.push(0), sb.push(0);
  for (int i = 1; i <= n; i++) {
    while (sa.size() > 1 && a[sa.top()] < a[i]) sa.pop();
    seg.modify(sa.top() + 1, i, 1, n, 1, SegTree::Tag(a[i], 0, 0, 0, 0, 0));
    sa.push(i);
    while (sb.size() > 1 && b[sb.top()] < b[i]) sb.pop();
    seg.modify(sb.top() + 1, i, 1, n, 1, SegTree::Tag(0, b[i], 0, 0, 0, 0));
    sb.push(i);
    seg.modify(1, i, 1, n, 1, SegTree::Tag(0, 0, 0, 0, 1, 0));
    for (auto [l, idx] : qry[i]) ans[idx] = seg.query(l, i, 1, n, 1).sh;
  }
  for (int i = 1; i <= q; i++) std::cout << ans[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
