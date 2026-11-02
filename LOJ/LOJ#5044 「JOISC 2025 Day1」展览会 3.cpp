/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;
constexpr int inf = 0x3f3f3f3f;

template<typename T> using pq =
  std::priority_queue<T, std::vector<T>, std::greater<T>>;

struct DeletableHeap {
  pq<int> pi, po;

  int top() {
    while (!po.empty() && po.top() == pi.top()) po.pop(), pi.pop();
    return pi.empty() ? inf : pi.top();
  }

  void ins(int val) { pi.push(val); }

  void del(int val) {
    if (top() == val) pi.pop();
    else po.push(val);
  }
};

struct SegTree {
  std::vector<DeletableHeap> tr;
  std::vector<int> mn;

  SegTree(int n) : tr((n << 2) + 20), mn((n << 2) + 20, inf) {}

  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }

  void pushup(int u) {
    mn[u] = std::min({mn[lc(u)], mn[rc(u)], tr[u].top()});
  }

  void modify(int l, int r, int s, int t, int u, int val, bool flg) {
    if (s <= l && r <= t) {
      if (flg) tr[u].ins(val);
      else tr[u].del(val);
      if (l == r) mn[u] = tr[u].top();
      else pushup(u);
      return;
    }
    int mid = (l + r) >> 1;
    if (s <= mid) modify(l, mid, s, t, lc(u), val, flg);
    if (t > mid) modify(mid + 1, r, s, t, rc(u), val, flg);
    pushup(u);
  }

  int query(int l, int r, int s, int t, int u) {
    if (s > t) return inf;
    if (s <= l && r <= t) return mn[u];
    int mid = (l + r) >> 1, ans = tr[u].top();
    if (s <= mid) ans = std::min(ans, query(l, mid, s, t, lc(u)));
    if (t > mid) ans = std::min(ans, query(mid + 1, r, s, t, rc(u)));
    return ans;
  }
};

struct DSU {
  std::vector<int> fa;

  DSU(int n) : fa(n) {
    std::iota(fa.begin(), fa.end(), 0);
  }

  int find(int u) { return u != fa[u] ? fa[u] = find(fa[u]) : u; }
  void merge(int u, int v) {
    int fau = find(u), fav = find(v);
    if (fau != fav) fa[fau] = fav;
  }
};

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n + 1);
  for (int i = 0, u; i < n; i++) std::cin >> u, a[u]++;

  SegTree seg(n);
  DSU dsu(m + 2);

  std::vector<int> l(m + 2), r(m + 2);
  for (int i = 1; i <= m; i++) {
    std::cin >> l[i] >> r[i];
    seg.modify(1, n, l[i], r[i], 1, i, true);
  }

  std::vector<int> idx(m + 2);

  auto check = [&](int u) {
    for (int i = 1; i <= u; i++) idx[i] = dsu.find(idx[i - 1] + 1);

    std::sort(idx.begin() + 1, idx.begin() + u + 1, [&](int lhs, int rhs) {
      return r[lhs] < r[rhs];
    });

    int cnt = 0, piv = 0;
    for (int i = 1; i <= u; i++) if (piv < l[idx[i]]) piv = r[idx[i]], cnt++;

    return cnt;
  };

  std::vector<int> ans(m + 1);

  std::vector<int> mx_r(n + 2), mn_l(n + 2);
  std::vector<pq<pii>> pq_l(n + 2), pq_r(n + 2);
  pq<pii> qq;

  int k = 0, cnt = 0;

  auto dfs = [&](auto &&self, int p) -> void {
    int pr = mx_r[p + 1], pl = mn_l[p - 1];

    for (; !pq_l[p].empty() && -pq_l[p].top().first > mx_r[p]; pq_l[p].pop()) {
      mx_r[p + 1] = std::min(mx_r[p + 1], pq_l[p].top().second);
    }
    for (; !pq_r[p].empty() && pq_r[p].top().first < mn_l[p]; pq_r[p].pop()) {
      mn_l[p - 1] = std::max(mn_l[p - 1], pq_r[p].top().second);
    }

    if (mx_r[p + 1] < pr) self(self, p + 1);
    if (mn_l[p - 1] > pl) self(self, p - 1);
  };

  auto update = [&](int u) {
    int v = seg.query(1, n, mn_l[u], mx_r[u], 1);
    if (v < inf) seg.modify(1, n, l[v], r[v], 1, v, false), qq.emplace(v, u);
  };

  for (int i = n, rst = m; rst && i; i--) {
    if (!a[i]) continue;

    k = cnt = 0;
    int w = 1;
    while (w <= rst && check(w) <= a[i]) {
      k = w;
      w <<= 1;
    }
    int lo = k + 1, hi = std::min(rst, w - 1);
    while (lo <= hi) {
      int mid = lo + ((hi - lo) >> 1), tmp = check(mid);
      if (tmp <= a[i]) lo = mid + 1, k = mid;
      else hi = mid - 1;
    }

    cnt = check(k);
    if (!k) continue;

    int piv = 0, cur = 0;
    for (int j = 1; j <= k; j++) {
      if (piv < l[idx[j]]) piv = mx_r[++cur] = r[idx[j]];
    }

    std::sort(idx.begin() + 1, idx.begin() + k + 1, [&](int lhs, int rhs) {
      return l[lhs] > l[rhs];
    });

    piv = n + 1, cur = cnt;
    for (int j = 1; j <= k; j++) {
      if (piv > r[idx[j]]) piv = mn_l[cur--] = l[idx[j]];
    }

    auto deal = [&](int p) {
      int u = std::lower_bound(mx_r.begin() + 1, mx_r.begin() + cnt + 1, l[p]) - mx_r.begin(),
          v = std::upper_bound(mn_l.begin() + 1, mn_l.begin() + cnt + 1, r[p]) - mn_l.begin() - 1;

      if (u > v) return seg.modify(1, n, l[p], r[p], 1, p, true);

      dsu.fa[p] = p + 1, rst--, ans[p] = i;

      if (u == v) {
        mn_l[u] = std::max(mn_l[u], l[p]);
        mx_r[u] = std::min(mx_r[u], r[p]);
        dfs(dfs, u);
      } else if (u + 1 == v) {
        pq_l[u].emplace(-l[p], r[p]);
        pq_r[v].emplace(r[p], l[p]);
      }
    };

    std::sort(idx.begin() + 1, idx.begin() + k + 1);
    for (int j = 1; j <= k; j++) {
      seg.modify(1, n, l[idx[j]], r[idx[j]], 1, idx[j], false);
      deal(idx[j]);
    }

    for (int j = 1; j <= cnt; j++) update(j);

    while (!qq.empty()) {
      auto [v, u] = qq.top();
      qq.pop();
      deal(v);
      update(u);
    }

    for (int j = 1; j <= cnt; j++) pq_l[j] = pq_r[j] = pq<pii>();
  }

  for (int i = 1; i <= m; i++) std::cout << ans[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  while (t--) solve();

  return 0;
}
