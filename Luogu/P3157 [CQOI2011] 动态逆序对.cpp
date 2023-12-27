/*
 * @file    P3157 [CQOI2011] 动态逆序对.cpp
 * @author  ForgotDream
 * @brief   Sqrt Data Structure
 * @date    2023-12-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 350;
int n, m;
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit[M];
int a[N];
int bcnt, blk;
int bln[N], lp[M], rp[M], siz[M];
bool del[N];
int pos[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i], pos[a[i]] = i;
  // blk = std::sqrt(n), bcnt = (n - 1) / blk + 1;
  blk = std::sqrt(17 * n), bcnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= bcnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk, siz[i] = blk;
  rp[bcnt] = n, siz[bcnt] = n - lp[bcnt] + 1;
  i64 ans = 0;
  for (int i = 1; i <= bcnt; i++) {
    for (int j = lp[i]; j <= rp[i]; j++) bit[i].modify(a[j], 1);
  }
  for (int i = 1; i <= n; i++) {
    ans += i - bit[bcnt + 1].query(a[i]) - 1;
    bit[bcnt + 1].modify(a[i], 1);
  }
  for (int u, b, p; m; m--) {
    std::cout << ans << "\n";
    std::cin >> u, p = pos[u], b = bln[p];
    for (int i = lp[b]; i < p; i++) ans -= (!del[i] && a[i] > u); 
    for (int i = p + 1; i <= rp[b]; i++) ans -= (!del[i] && a[i] < u); 
    for (int i = 1; i < b; i++) ans -= siz[i] - bit[i].query(u);
    for (int i = b + 1; i <= bcnt; i++) ans -= bit[i].query(u);
    bit[b].modify(u, -1), siz[b]--, del[p] = true;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
