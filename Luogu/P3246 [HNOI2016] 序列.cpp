/**
 * @file    P3246 [HNOI2016] 序列.cpp
 * @author  ForgotDream
 * @brief   Monotone Stack
 * @date    2023-08-20
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 100050, M = 22;
int k, n, q;
i64 a[N];
int lp[N], rp[N];
i64 fl[N], fr[N], sl[N], sr[N];
i64 st[M][N], lg[N];

void init() {
  lg[1] = 0;
  for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
  for (int i = 1; i <= n; i++) st[0][i] = i;
  for (int i = 1; i <= lg[n]; i++) {
    for (int j = 1; j + (1 << i) - 1 <= n; j++) {
      if (a[st[i - 1][j]] < a[st[i - 1][j + (1 << (i - 1))]]) {
        st[i][j] = st[i - 1][j];
      } else {
        st[i][j] = st[i - 1][j + (1 << (i - 1))];
      }
    }
  }
}

i64 query(int l, int r) {
  int k = lg[r - l + 1];
  return a[st[k][l]] < a[st[k][r - (1 << k) + 1]]
             ? st[k][l]
             : st[k][r - (1 << k) + 1];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  init();
  std::stack<int> s;
  std::fill(rp + 1, rp + n + 1, n + 1);
  for (int i = 1; i <= n; i++) {
    while (!s.empty() && a[s.top()] > a[i]) rp[s.top()] = i, s.pop();
    if (!s.empty()) lp[i] = s.top();
    s.push(i);
  }
  for (int i = 1; i <= n; i++) {
    fr[i] = a[i] * (i - lp[i]) + fr[lp[i]];
    sr[i] = sr[i - 1] + fr[i];
  }
  for (int i = n; i >= 1; i--) {
    fl[i] = a[i] * (rp[i] - i) + fl[rp[i]];
    sl[i] = sl[i + 1] + fl[i];
  }

  for (int i = 1, l, r; i <= q; i++) {
    std::cin >> l >> r;
    auto p = query(l, r);
    std::cout << (p - l + 1) * (r - p + 1) * a[p] + 
                     sr[r] - sr[p] - fr[p] * (r - p) + 
                     sl[l] - sl[p] - fl[p] * (p - l)
              << "\n";
  }

  return 0;
}