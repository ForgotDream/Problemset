/**
 * @file    AT_arc157_d [ARC157D] YY Garden.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-07-31
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2050, mod = 998244353;
int H, W;
char S[N][N];
int sum[N][N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> H >> W;
  for (int i = 1; i <= H; i++) {
    for (int j = 1; j <= W; j++) {
      std::cin >> S[i][j];
      sum[i][j] = (S[i][j] == 'Y') + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    }
  }
  int pair = sum[H][W] / 2;
  if (sum[H][W] & 1 || pair == 0) {
    std::cout << 0 << "\n";
    return 0;
  }

  i64 ans = 0;
  for (int h = 0; h < H; h++) {
    if (pair % (h + 1) != 0) continue;
    int w = pair / (h + 1) - 1;
    i64 deg = 1;
    std::vector<int> hC(1), wC(1);
    
    for (int i = 1, cur = 2 * (w + 1); hC.size() <= h; i++) {
      if (sum[i][W] > cur) break;
      else if (sum[i][W] == cur) {
        hC.push_back(i);
        cur += 2 * (w + 1);
        int j = 1;
        for (i++, j = 1; sum[i][W] == sum[i - 1][W]; i++, j++);
        deg = deg * j % mod, i--;
      }
    }
    if (hC.size() != h + 1) continue;
    hC.push_back(H);

    for (int i = 1, cur = 2 * (h + 1); wC.size() <= w; i++) {
      if (sum[H][i] > cur) break;
      else if (sum[H][i] == cur) {
        wC.push_back(i);
        cur += 2 * (h + 1);
        int j = 1;
        for (i++, j = 1; sum[H][i] == sum[H][i - 1]; i++, j++);
        deg = deg * j % mod, i--;
      }
    }
    if (wC.size() != w + 1) continue;
    wC.push_back(W);

    bool flg = true;
    for (int i = 1; i < hC.size(); i++) {
      for (int j = 1; j < wC.size(); j++) {
        if (sum[hC[i]][wC[j]] - sum[hC[i - 1]][wC[j]] - sum[hC[i]][wC[j - 1]] 
            + sum[hC[i - 1]][wC[j - 1]] != 2) {
          flg = false;
          break;
        }
      }
      if (!flg) break;
    }
    if (!flg) continue;

    (ans += deg) %= mod;
  }

  std::cout << ans << "\n";

  return 0;
}