/**
 * @file    CF1208F Bits And Pieces.cpp
 * @author  ForgotDream
 * @brief   高维前缀和？
 * @date    2023-08-01
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50, K = 21, M = 3e6 + 50;
int n, a[N];
int max[M], semi[M];

void chkmax(int idx, int val) {
  if (max[idx] < val) semi[idx] = max[idx], max[idx] = val;
  else semi[idx] = std::max(semi[idx], val);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], chkmax(a[i], i);

  for (int i = 0; i < K; i++) {
    for (int j =  0; j < 1 << K; j++) {
      if (!(j & (1 << i))) 
        chkmax(j, max[j ^ (1 << i)]), chkmax(j, semi[j ^ (1 << i)]);
    }
  }

  int mask = (1 << K) - 1, ans = 0;
  for (int i = 1; i <= n - 2; i++) {
    int inv = a[i] ^ mask, tmp = 0;
    for (int j = 21; j >= 0; j--) {
      if (inv & (1 << j) && semi[tmp ^ (1 << j)] > i) tmp ^= (1 << j);
    }
    ans = std::max(ans, tmp | a[i]);
  }

  std::cout << ans << "\n";

  return 0;
}
