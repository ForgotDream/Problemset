/**
 * @file    CF837G Functions On The Segments.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-10-27
 */
#include <iostream>

using i64 = long long;
using pll = std::pair<i64, i64>;

constexpr int N = 1e5 + 50, mod = 1e9;
int n, m;
struct SegTree {
  struct Node {
    i64 l, r, k, b;
    int lc, rc;
  } tree[N << 7];
  int cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void pushup(int u) {
    tree[u].k = tree[lc(u)].k + tree[rc(u)].k;
    tree[u].b = tree[lc(u)].b + tree[rc(u)].b;
  }
  void modify(int tar, int s, int t, int &u, int v, i64 k, i64 b) {
    u = ++cnt, tree[u] = tree[v];
    if (s == t) return tree[u].k += k, tree[u].b += b, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), lc(v), k, b);
    else modify(tar, mid + 1, t, rc(u), rc(v), k, b);
    pushup(u);
  }
  struct Result {
    i64 k, b;
    Result &operator+=(const Result &rhs) {
      return k += rhs.k, b += rhs.b, *this;
    }
    Result &operator-=(const Result &rhs) {
      return k -= rhs.k, b -= rhs.b, *this;
    }
  };
  Result query(int l, int r, int s, int t, int u) {
    if (!u) return {0, 0};
    if (l <= s && t <= r) return {tree[u].k, tree[u].b};
    int mid = (s + t) >> 1;
    Result res = {0, 0};
    if (mid >= l) res += query(l, r, s, mid, lc(u));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u));
    return res;
  }
} seg;
int rt[N];
void solve() {
  std::cin >> n;
  int s = 0, t = 1e9;
  for (int i = 1; i <= n; i++) {
    int l, r, k, b, a1, a2;
    std::cin >> l >> r >> a1 >> k >> b >> a2;
    seg.modify(0, s, t, rt[i], rt[i - 1], 0, a1);
    seg.modify(l + 1, s, t, rt[i], rt[i], k, b - a1);
    seg.modify(r + 1, s, t, rt[i], rt[i], -k, a2 - b);
  }
  std::cin >> m;
  i64 lst = 0;
  for (int l, r, x; m; m--) {
    std::cin >> l >> r >> x;
    x = (x + lst) % mod;
    auto cur = seg.query(0, x, s, t, rt[r]);
    cur -= seg.query(0, x, s, t, rt[l - 1]);
    std::cout << (lst = cur.k * x + cur.b) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
