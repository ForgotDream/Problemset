/*
 * @file    P3688 [ZJOI2017] 树状数组.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-18
 */
#include <bits/stdc++.h>

using i64 = long long;

// 其实就是等价于询问 a_{l - 1} \equiv a_{r} \pmod{2} 的概率
// 更进一步的就是奇偶性相同，这个怎么刻画？
// 对于一个询问，考虑把之前的修改分为几种：
// 1. 包含两端点的
// 2. 包含其中一个端点的
// 3. 不包含端点的
// 还有么？
// 然后，额，考虑二维数点，就可以求出这几种修改的个数
// 然后是不是就是个数学题了？不是很懂
constexpr int N = 1e5 + 50, mod = 998244353;
int n, m;

inline i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline i64 inv(i64 u) { return fastPow(u, mod - 2, mod); }

inline int calc(int u, int v) {
  int res = 1ll * u * v % mod;
  res = (res + (1ll - u + mod) * (1ll - v + mod) % mod) % mod;
  return res;
}

struct InnerSegTree {
  struct Node {
    int lc, rc, val;
  } tree[N << 9];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  void modify(int l, int r, int s, int t, int &u, int val) {
    if (!u) u = ++cnt, tree[u].val = 1;
    if (l <= s && t <= r) return tree[u].val = calc(val, tree[u].val), void();
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
  }
  int query(int tar, int s, int t, int u) {
    if (!u) return 1;
    if (s == t) return tree[u].val;
    int mid = (s + t) >> 1;
    if (mid >= tar) return calc(tree[u].val, query(tar, s, mid, lc(u)));
    else return calc(tree[u].val, query(tar, mid + 1, t, rc(u)));
  }
} s1;

struct OutterSegTree {
  int rt[N << 2];
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  void modify(int l, int r, int s, int t, int u, int ll, int rr, int val) {
    // std::cerr << l << " " << r << " " << s << " " << t << "\n";
    if (l <= s && t <= r) return s1.modify(ll, rr, 1, n, rt[u], val);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), ll, rr, val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), ll, rr, val);
  }
  int query(int tar, int s, int t, int u, int pos) {
    if (s == t) return s1.query(pos, 1, n, rt[u]);
    int mid = (s + t) >> 1, cur = s1.query(pos, 1, n, rt[u]);
    if (mid >= tar) return calc(cur, query(tar, s, mid, lc(u), pos));
    else return calc(cur, query(tar, mid + 1, t, rc(u), pos));
  }
} s2;

void solve() {
  std::cin >> n >> m;
  for (int i = 1, opt, l, r; i <= m; i++) {
    std::cin >> opt >> l >> r;
    if (opt == 1) {
      int v = inv(r - l + 1);
      if (l > 1) {
        s2.modify(1, l - 1, 0, n, 1, l, r, (1 - v + mod) % mod);
        s2.modify(0, 0, 0, n, 1, 1, l - 1, 0);
      }
      if (r < n) {
        s2.modify(l, r, 0, n, 1, r + 1, n, (1 - v + mod) % mod);
        s2.modify(0, 0, 0, n, 1, r + 1, n, 0);
      }
      s2.modify(l, r, 0, n, 1, l, r, (1 - 2ll * v % mod + mod) % mod);
      s2.modify(0, 0, 0, n, 1, l, r, v);
    } else {
      std::cout << s2.query(l - 1, 0, n, 1, r) << "\n";
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
