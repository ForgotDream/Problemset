/*
 * @file    P3809 【模板】后缀排序.cpp
 * @author  ForgotDream
 * @brief   SA
 * @date    2024-01-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50;

int n;
char s[N];

int b[N], sa[N], rk[N];

void getSA() {
  static int pre[N], id[N], lst[N];


  int sig = 127;
  for (int i = 1; i <= n; i++) b[rk[i] = s[i]]++;
  for (int i = 1; i <= sig; i++) b[i] += b[i - 1];
  for (int i = n; i >= 1; i--) sa[b[rk[i]]--] = i;

  int rc = 0;  // rc stands for `rank count`
  for (int w = 1;; w <<= 1, sig = rc) {
    auto cmp = [&](int x, int y) { 
      return lst[x] == lst[y] && lst[x + w] == lst[y + w]; 
    };

    rc = 0;
    for (int i = n; i > n - w; i--) id[++rc] = i;
    for (int i = 1; i <= n; i++) if (sa[i] > w) id[++rc] = sa[i] - w;

    memset(b, 0, sizeof(b));
    for (int i = 1; i <= n; i++) b[pre[i] = rk[id[i]]]++;
    for (int i = 1; i <= sig; i++) b[i] += b[i - 1];

    for (int i = n; i >= 1; i--) sa[b[pre[i]]--] = id[i];
    memcpy(lst + 1, rk + 1, sizeof(int) * n);
    rc = 0;
    for (int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? rc : ++rc;

    if (rc >= n) return;
  }
}

void solve() {
  std::cin >> (s + 1);
  n = strlen(s + 1);

  getSA();

  for (int i = 1; i <= n; i++) std::cout << sa[i] << " \n"[i == n];
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
