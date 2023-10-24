/**
 * @file    P5056 插头 dp.cpp
 * @author  ForgotDream
 * @brief   Plug DP
 * @date    2023-06-12
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 299993, siz = 3e5;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> bit(m + 1);
  bit[0] = 1;
  for (int i = 1; i <= m; i++) { bit[i] = bit[i - 1] << 2; }

  std::vector a(n + 1, std::vector<bool>(m + 1));
  int ex = 0, ey = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      std::cin >> c;
      if (c == '.') { a[i][j] = true, ex = i, ey = j; }
    }
  }

  std::vector f(2, std::vector<i64>(siz));
  std::vector stt(2, std::vector<i64>(siz));
  int cur = 0;

  std::vector<int> head(siz), nxt(siz);
  std::array<int, 2> cnt { 0, 0 };
  auto insert = [&](int st, i64 num) {
    int curSt = st % mod + 1;
    for (int i = head[curSt]; i; i = nxt[i]) {
      if (st == stt[cur][i]) { 
        f[cur][i] += num;
        return; 
      }
    }
    nxt[cnt[cur]] = head[curSt], head[curSt] = cnt[cur];
    stt[cur][cnt[cur]] = st, f[cur][cnt[cur]] = num;
    cnt[cur]++;
  };

  auto valid = [&](int x, int y) {
    if (x > n || y > m) { return false; }
    return !!a[x][y];
  };

  i64 ans = 0;
  cnt[cur] = 1, f[cur][0] = 1, stt[cur][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < cnt[cur]; j++) { stt[cur][j] <<= 2; }
    for (int j = 1; j <= m; j++) {
      cur ^= 1;
      int lst = cur ^ 1;
      head.assign(siz, 0), cnt[cur] = 0;
      for (int k = 0; k < cnt[lst]; k++) {
        int st = stt[lst][k];
        int b1 = (st >> ((j - 1) * 2)) % 4, b2 = (st >> (j * 2)) % 4;
        i64 num = f[lst][k];
        if (!a[i][j]) {
          if (!b1 && !b2) { insert(st, num); }
        } else if (!b1 && !b2) {
          if (valid(i + 1, j) && valid(i, j + 1)) {
            insert(st + bit[j - 1] + bit[j] * 2, num);
          }
        } else if (!b1 && b2) {
          if (valid(i, j + 1)) { insert(st, num); }
          if (valid(i + 1, j)) { insert(st + b2 * (bit[j - 1] - bit[j]), num); }
        } else if (b1 && !b2) {
          if (valid(i + 1, j)) { insert(st, num); }
          if (valid(i, j + 1)) { insert(st + b1 * (bit[j] - bit[j - 1]), num); }
        } else if (b1 == 1 && b2 == 1) {
          int p = 1;
          for (int l = j + 1; l <= m; l++) {
            if ((st >> (l * 2)) % 4 == 1) { ++p; }
            if ((st >> (l * 2)) % 4 == 2) { --p; }
            if (!p) {
              insert(st - bit[j] - bit[j - 1] - bit[l], num);
              break;
            }
          }
        } else if (b1 == 2 && b2 == 2) {
          int p = 1;
          for (int l = j - 2; l >= 0; l--) {
            if ((st >> (l * 2)) % 4 == 1) { --p; }
            if ((st >> (l * 2)) % 4 == 2) { ++p; }
            if (!p) {
              insert(st - 2 * (bit[j] + bit[j - 1]) + bit[l], num);
              break;
            }
          }
        } else if (b1 == 2 && b2 == 1) {
          insert(st - 2 * bit[j - 1] - bit[j], num);
        } else if (i == ex && j == ey) {
          ans += num;
        }
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}