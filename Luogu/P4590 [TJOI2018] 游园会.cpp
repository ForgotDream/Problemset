/**
 * @file    P4590 [TJOI2018] 游园会.cpp
 * @author  ForgotDream
 * @brief   DP of DP
 * @date    2023-07-28
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e3 + 50, K = 20, mod = 1e9 + 7;
constexpr char sigma[] = { 'N', 'O', 'I' };
int n, k;
i64 f[2][1 << K][3], nxt[1 << K][3], ans[N];
char s[K];

int hsh[K], trans[K];
auto decode(int cur) {
  for (int i = 0; i < k; i++) {
    hsh[i] = (i ? hsh[i - 1] : 0) + (cur & 1);
    cur >>= 1;
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k >> s;
  int st = 1 << k;
  for (int i = 0; i < st; i++) {
    decode(i);
    for (int j = 0; j < 3; j++) {
      int nxt = 0;
      for (int k = 0; k < ::k; k++) {
        if (s[k] == sigma[j]) trans[k] = (k ? hsh[k - 1] : 0) + 1;
        else trans[k] = std::max(hsh[k], k ? trans[k - 1] : 0);
        nxt += (1 << k) * (trans[k] - (k ? trans[k - 1] : 0));
      }
      ::nxt[i][j] = nxt;
    }
  }

  f[0][0][0] = 1;
  int cur = 1, pre = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < st; j++) f[cur][j][0] = f[cur][j][1] = f[cur][j][2] = 0;
    for (int j = 0; j < st; j++) {
      (f[cur][nxt[j][0]][1] += f[pre][j][0] + f[pre][j][1] + f[pre][j][2]) %= mod;
      (f[cur][nxt[j][1]][0] += f[pre][j][0] + f[pre][j][2]) %= mod;
      (f[cur][nxt[j][1]][2] += f[pre][j][1]) %= mod;
      (f[cur][nxt[j][2]][0] += f[pre][j][0] + f[pre][j][1]) %= mod;
    }
    std::swap(cur, pre);
  }

  for (int i = 0; i < st; i++) {
    int cnt = std::__popcount(i);
    (ans[cnt] += f[pre][i][0] + f[pre][i][1] + f[pre][i][2]) %= mod;
  }
  for (int i = 0; i <= k; i++) std::cout << ans[i] << "\n";

  return 0;
}