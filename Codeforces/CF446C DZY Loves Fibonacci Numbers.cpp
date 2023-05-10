/**
 * @file    CF446C DZY Loves Fibonacci Numbers.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + Math
 * @date    2023-05-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 MOD = 1e9 + 9;
constexpr i64 inv1 = 276601605, inv2 = 691504013, inv3 = 308495997;

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  while (exp) {
    if (exp & 1) {
      (res *= base) %= mod;
    }
    (base *= base) %= mod;
    exp >>= 1;
  }
  return res;
}

struct SegTree {
  int n;
  struct Node {
    i64 sum, tag;
    Node() {
      sum = tag = 0;
    }
  };
  std::vector<Node> tr;
  i64 base, inv;
  std::vector<i64> prod;
  
  SegTree(int _n, i64 _b) {
    n = _n;
    base = _b;
    inv = fastPow(base - 1, MOD - 2, MOD);
    tr.resize((n << 2) + 1);
    prod.resize(n + 1);
    prod[0] = 1;
    for (int i = 1; i <= n; i++) {
      (prod[i] = prod[i - 1] * base) %= MOD;
    }
  }

  void tagging(int u, int l, int r, i64 val) {
    (tr[u].tag += val) %= MOD;
    (tr[u].sum += val * ((prod[r - l + 1] - 1) % MOD + MOD) % MOD * inv) %= MOD;
  }

  Node pushup(const Node &lhs, const Node &rhs) {
    Node res;
    (res.sum = lhs.sum + rhs.sum) %= MOD;
    return res;
  }

  void pushdown(int u, int l, int r) {
    if (!tr[u].tag) {
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    tagging(lc, l, mid, tr[u].tag);
    tagging(rc, mid + 1, r, (tr[u].tag * prod[mid - l + 1]) % MOD);
    tr[u].tag = 0;
  }

  void modify(int l, int r, int s, int t, int u, int val) {
    if (l == s && t == r) {
      // std::cerr << s << " " << t << " " << val << "\n";
      tagging(u, s, t, val);
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    pushdown(u, s, t);
    if (r <= mid) {
      modify(l, r, s, mid, lc, val);
    } else if (l > mid) {
      modify(l, r, mid + 1, t, rc, val);
    } else {
      modify(l, mid, s, mid, lc, val);
      modify(mid + 1, r, mid + 1, t, rc, (val * prod[mid - l + 1]) % MOD);
    }
    tr[u] = pushup(tr[lc], tr[rc]);
  }

  i64 query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) {
      return tr[u].sum;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    i64 res = 0;
    pushdown(u, s, t);
    if (l <= mid) {
      (res += query(l, r, s, mid, lc)) %= MOD;
    }
    if (r > mid) {
      (res += query(l, r, mid + 1, t, rc)) %= MOD;
    }
    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  std::vector<i64> sum(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> sum[i];
    (sum[i] += sum[i - 1]) %= MOD;
  }

  SegTree t1(n, inv2), t2(n, inv3);
  for (int i = 0; i < m; i++) {
    int opt, l, r;
    std::cin >> opt >> l >> r;
    if (opt == 1) {
      t1.modify(l, r, 1, n, 1, inv2);
      t2.modify(l, r, 1, n, 1, inv3);
    } else {
      i64 x = t1.query(l, r, 1, n, 1), y = t2.query(l, r, 1, n, 1);
      // std::cerr << x << " " << y << "\n";
      std::cout << (inv1 * ((x - y) % MOD + MOD) % MOD + (sum[r] - sum[l - 1]) % MOD + MOD) % MOD << "\n";
    }
  }

  return 0;
}