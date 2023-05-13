#include <bits/stdc++.h>

using i64 = long long;

struct SegTree {
  int n;
  struct Node {
    int max, cnt, min;
    int l, r;
  };
  std::vector<Node> tr;
  std::vector<int> a;

  SegTree(int _n, const std::vector<int> &_a) {
    n = _n;
    tr.resize((n << 2) + 1);
    a = _a;
  }

  Node pushup(const Node &lhs, const Node &rhs) {
    Node res;
    res.max = std::max(lhs.max, rhs.max);
    res.min = std::min(lhs.min, rhs.min);
    res.l = lhs.l, res.r = rhs.r;
    return res;
  }

  void build(int l, int r, int u) {
    if (l == r) {
      tr[u].max = tr[u].min = tr[u].l = tr[u].r = a[l];
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
    tr[u] = pushup(tr[lc], tr[rc]);
  }

  void modify(int target, int s, int t, int u, int val) {
    if (s == target && t == target) {
      tr[u].max = tr[u].min = tr[u].l = tr[u].r = val;
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (target <= mid) {
      modify(target, s, mid, lc, val);
    } else {
      modify(target, mid + 1, t, rc, val);
    }
    tr[u] = pushup(tr[lc], tr[rc]);
  }

  Node query(int s, int t, int u, int val) {
    if (tr[u].max < val) {
      tr[u].cnt = 0;
      return tr[u];
    }
    if (tr[u].min >= val) {
      tr[u].cnt = 1;
      return tr[u];
    }
    if (s == t) {
      tr[u].cnt = (tr[u].max >= val);
      return tr[u];
    }
    Node res;
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    Node lhs = query(s, mid, lc, val), rhs = query(mid + 1, t, rc, val);
    res = pushup(lhs, rhs);
    if (lhs.r < val || rhs.l < val) {
      res.cnt = lhs.cnt + rhs.cnt;
    } else {
      res.cnt = lhs.cnt + rhs.cnt - 1;
    }
    return res;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  SegTree st(n, a);
  st.build(1, n, 1);

  int lst = 0;
  for (int i = 0; i < m; i++) {
    char opt;
    std::cin >> opt;
    if (opt == 'C') {
      int k, y;
      std::cin >> k >> y;
      k ^= lst, y ^= lst;
      st.modify(k, 1, n, 1, y);
    } else {
      int x, f;
      std::cin >> x;
      x ^= lst;
      f = st.query(1, n, 1, x).cnt;
      std::cout << f << "\n";
      lst = f;
    }
  }

  return 0;
}