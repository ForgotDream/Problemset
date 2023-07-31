/**
 * @file    CF833B The Bakery.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-07-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e4 + 50, K = 55;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
int n, k, a[N];
i64 f[K][N], cnt[N], cur;
int s, t;

i64 calc(int l, int r) {
#define c1 cnt[a[s]]
#define c2 cnt[a[t]]
  while (s > l) s--, c1++, cur += (c1 == 1);
  while (s < l) c1--, cur -= (c1 == 0), s++;
  while (t < r) t++, c2++, cur += (c2 == 1);
  while (r < t) c2--, cur -= (c2 == 0), t--;
  return cur;
#undef c1
#undef c2
}

void solve(int l, int r, int s, int t, int k) {
  if (l > r) return;
  int mid = (l + r) >> 1, pivot = s;
  i64 ans = -inf;
  for (int i = s; i <= std::min(t, mid); i++) {
    auto tmp = f[k - 1][i - 1] + calc(i, mid);
    if (tmp > ans) ans = tmp, pivot = i;
  };
  f[k][mid] = ans;
  solve(l, mid - 1, s, pivot, k);
  solve(mid + 1, r, pivot, t, k);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i], f[0][i] = -inf;
  s = t = 1, cnt[a[1]]++, cur = 1;
  for (int i = 1; i <= k; i++) solve(1, n, 1, n, i);
  std::cout << f[k][n] << "\n";

  return 0;
}