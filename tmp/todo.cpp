/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-19
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, f[N], t[N], a[N], b[N], c[N], d[N];
std::vector<int> disca, discb;
struct SegTree {
  struct Node {
    int lc, rc;
    i64 sum, tag;
  } tree[N << 5];
  int rt[N], cnt;
  inline &int lc(int u) { return tree[u].lc; }
  inline &int rc(int u) { return tree[u].rc; }
  void modify(int l, int r, int s, int t, int u, int v, i64 val) {
    tree[u] = tree[v];
    if (l <= s && t <= r) return tree[u].tag += val, void();
    int mid = (s + t) >> 1;
    if (mid >= l && s <= r) lc(u) = ++cnt, modify(l, r, s, mid, lc(u), lc(v), val); 
    if (mid < r && t >= l) rc(u) = ++cnt, modify(l, r, mid + 1, t, rc(u), rc(v), val);
    tree[u].sum += val * (std::min(t, r) - std::max(s, l) + 1);
  }
  i64 query(int tar, int s, int t, int u, i64 tag) {
    if (l <= s && t <= r) return tree[u].sum + (t - s + 1) * tag;
    int mid = (s + t) >> 1;
    if (mid >= tar) return query(tar, s, mid, lc(u), tag + tree[u].tag);
    else return query(tar, mid + 1, t, rc(u), tag + tree[u].tag);
  }
} seg;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> f[i];
  for (int i = 1; i <= n; i++) std::cin >> t[i];
  for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i], disca.push_back(a[i]), disca.push_back(b[i]);
  for (int i = 1; i <= n; i++) std::cin >> c[i] >> d[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
