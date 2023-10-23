/**
 * @file    P3747 [六省联考 2017] 相逢是问候.cpp
 * @author  ForgotDream
 * @brief   SegTree + Math
 * @date    2023-10-20
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 55, BLK = 1e4;
int n, m, p, c, a[N];
int cnt, phi[M];
i64 pw1[M][N], pw2[M][N];
bool of1[M][N], of2[M][N];
int getPhi(int p) {
  int res = p;
  for (int i = 2; i * i <= p; i++) {
    if (p % i == 0) {
      res = 1ll * res * (i - 1) / i;
      while (p % i == 0) p /= i;
    }
  }
  if (p != 1) res = 1ll * res * (p - 1) / p;
  return res;
}
void init() {
  int cur = p;
  phi[0] = p;
  while (cur != 1) cur = getPhi(cur), phi[++cnt] = cur;
  phi[++cnt] = 1;
  for (int i = 0; i <= cnt; i++) {
    pw1[i][0] = 1;
    for (int j = 1; j <= BLK; j++) {
      pw1[i][j] = c * pw1[i][j - 1];
      if (pw1[i][j] >= phi[i]) of1[i][j] = true, pw1[i][j] %= phi[i];
      of1[i][j] |= of1[i][j - 1];
    }
  }
  for (int i = 0; i <= cnt; i++) {
    pw2[i][0] = 1, of2[i][1] = of1[i][BLK];
    for (int j = 1; j <= BLK; j++) {
      pw2[i][j] = pw1[i][BLK] * pw2[i][j - 1];
      if (pw2[i][j] >= phi[i]) of2[i][j] = true, pw2[i][j] %= phi[i];
      of2[i][j] |= of2[i][j - 1];
    }
  }
}
bool flg;
int calc(int i, int j) {
  flg = false;
  int i1 = i % BLK, i2 = i / BLK;
  i64 res = pw1[j][i1] * pw2[j][i2];
  if (res >= phi[j]) res %= phi[j], flg = true;
  flg |= of1[j][i1] | of2[j][i2];
  return res;
}
int dfs(int val, int cur, int lim) {
  flg = false;
  if (cur == lim) {
    if (val >= phi[lim]) val %= phi[lim], flg = true;
    return val;
  }
  int nxt = dfs(val, cur + 1, lim);
  return calc(flg ? nxt + phi[cur + 1] : nxt, cur);
}
struct SegTree {
  i64 sum[N << 2], mincnt[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) {
    sum[u] = sum[lc(u)] + sum[rc(u)];
    if (sum[u] > p) sum[u] -= p;
    mincnt[u] = std::min(mincnt[lc(u)], mincnt[rc(u)]);
  }
  void build(int s, int t, int u) {
    if (s == t) return sum[u] = a[s], void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int l, int r, int s, int t, int u) {
    if (s == t) return mincnt[u]++, sum[u] = dfs(a[s], 0, mincnt[u]), void();
    int mid = (s + t) >> 1;
    if (mid >= l && mincnt[lc(u)] < cnt) modify(l, r, s, mid, lc(u));
    if (mid < r && mincnt[rc(u)] < cnt) modify(l, r, mid + 1, t, rc(u));
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return sum[u];
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u));
    return res >= p ? res - p : res;
  }
} seg;
void solve() {
  std::cin >> n >> m >> p >> c;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  init(), seg.build(1, n, 1);
  for (int opt, l, r; m; m--) {
    std::cin >> opt >> l >> r;
    if (!opt) seg.modify(l, r, 1, n, 1);
    else std::cout << seg.query(l, r, 1, n, 1) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
