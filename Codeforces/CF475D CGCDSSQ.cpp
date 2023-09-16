/**
 * @file    CF475D CGCDSSQ.cpp
 * @author  ForgotDream
 * @brief   ST + Math
 * @date    2023-09-08
 */
#include <iostream>
#include <map>
#include <numeric>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 3e5 + 50, K = 20;
int n, a[N], q, qry[M];
int lg[N], st[K][N];
std::map<int, i64> ans;
void init() {
  for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
  for (int i = 1; i <= n; i++) st[0][i] = a[i];
  for (int i = 1; i < K; i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      st[i][j] = std::gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}
int query(int l, int r) {
  int k = lg[r - l + 1];
  return std::gcd(st[k][l], st[k][r - (1 << k) + 1]);
}
int find(int l, int r, int g) {
  int lo = r, hi = n, res = 0;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (query(l, mid) == g) res = mid, lo = mid + 1;
    else hi = mid - 1; 
  }
  return res;
}
void calc(int l) {
  int lst, r = l, g = a[l];
  while (true) {
    lst = r, r = find(l, r, g);
    ans[g] += r - lst + 1;
    if (r == n) return;
    r++, g = query(l, r);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  init();
  std::cin >> q;
  for (int i = 1; i <= q; i++) std::cin >> qry[i];
  for (int i = 1; i <= n; i++) calc(i);
  for (int i = 1; i <= q; i++) std::cout << ans[qry[i]] << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}