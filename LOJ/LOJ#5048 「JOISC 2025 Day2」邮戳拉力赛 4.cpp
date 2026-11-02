/*
 * @file    LOJ#5048 「JOISC 2025 Day2」邮戳拉力赛 4.cpp
 * @author  ForgotDream
 * @brief
 * @date    2026-10-28
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pll = std::pair<i64, i64>;

void solve() {
  int n, x;
  std::cin >> n >> x;
  int m = 2 * n;

  std::vector<i64> a(2 * m), c(m);
  for (int i = 0; i < m; i++) std::cin >> a[i], a[i + m] = a[i];
  for (int i = 0; i < m; i++) std::cin >> c[i];

  i64 cr = 0, cur = 0;
  std::vector<int> cnt(n + 1), nxt(m), pre(n + 1);
  for (int i = 0; i < m; i++) {
    cnt[a[i]]++;
    if (cnt[a[i]] == 1) {
      pre[a[i]] = i;
      cur += cr;
    } else {
      cr++;
      nxt[pre[a[i]]] = i;
      nxt[i] = pre[a[i]] + m;
    }
  }

  std::vector<pll> states(m);
  for (int i = 0; i < m; i++) {
    states[i] = {cur, c[i]};
    cur += nxt[i] - i - n;
  }
  std::sort(states.begin(), states.end());

  std::vector<i64> pre_min(m), suf_min(m);
  pre_min[0] = states[0].second;
  for (int i = 1; i < m; i++) pre_min[i] = std::min(pre_min[i - 1], states[i].second);
  suf_min[m - 1] = states[m - 1].second + states[m - 1].first * x;
  for (int i = m - 2; ~i; i--) suf_min[i] = std::min(suf_min[i + 1], states[i].second + states[i].first * x);

  // for (int i = 0; i < m; i++) std::cerr << states[i].first << " " << states[i].second << "\n";

  int q;
  std::cin >> q;

  for (int i = 1; i <= q; i++) {
    i64 k;
    std::cin >> k;
    k = 1ll * n * n - k;

    auto idx = std::upper_bound(states.begin(), states.end(), pll{k, 0ll}) - states.begin();
    i64 ans = 4e18;
    if (idx) ans = std::min(ans, pre_min[idx - 1]);
    if (idx < m) ans = std::min(ans, suf_min[idx] - k * x);
    std::cout << ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
