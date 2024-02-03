#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 4e5 + 50;

struct SegTree {
  struct MyStruct {
    int lc, rc;
    i64 sum;
  } tree[N << 5];
  int cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void pushup(int u) {
    tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum;
  }
  inline int clone(int u) { return tree[++cnt] = tree[u], cnt; }
  void modify(int tar, int &u, int v, int s, int t, i64 val) {
    u = clone(v);
    if (s == t) return tree[u].sum += val, void();
    int mid = (s + t) >> 1;
    if (tar <= mid) modify(tar, lc(u), lc(v), s, mid, val);
    else modify(tar, rc(u), rc(v), mid + 1, t, val);
    pushup(u);
  }
  i64 query(int l, int r, int s, int t, int u) {
    if (!u) return 0;
    if (l <= s && t <= r) return tree[u].sum;
    i64 res = 0;
    int mid = (s + t) >> 1;
    if (l <= mid) res += query(l, r, s, mid, lc(u));
    if (r > mid) res += query(l, r, mid + 1, t, rc(u));
    return res;
  }
} seg;

std::vector<int> b;

inline int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}

int n, q, a[N], rt[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i], b.push_back(a[i]), b.push_back(a[i] - 1);
  }
  b.push_back(INT_MAX);

  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  int m = b.size();

  for (int i = 1; i <= n; i++) {
    seg.modify(find(a[i]), rt[i], rt[i - 1], 1, m, a[i]);
  }

  std::cin >> q;

  i64 lst = 0;
  for (i64 l, r, v; q; q--) {
    std::cin >> l >> r >> v, l ^= lst, r ^= lst, v ^= lst;
    if (l > r) std::swap(l, r);
    int u = find(v);
    lst = seg.query(1, u, 1, m, rt[r]) - seg.query(1, u, 1, m, rt[l - 1]);
    std::cout << lst << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}



