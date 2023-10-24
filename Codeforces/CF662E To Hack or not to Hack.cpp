/**
 * @file    CF662E To Hack or not to Hack.cpp
 * @author  ForgotDream
 * @brief   DP + DFS
 * @date    2023-09-07
 */
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

#pragma region
namespace FastIO {
constexpr signed bufsize = 1 << 24;
char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
char outbuf[bufsize], *pp = outbuf;
inline char gc() {
  if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, bufsize, stdin);
  return p1 == p2 ? EOF : *p1++;
}
template <typename T>
inline void read(T &x) {
  x = 0;
  T f = 1;
  char c = gc();
  while (!isdigit(c)) f = ( c == '-' ? -f : f), c = gc();
  while (isdigit(c)) x = x * 10 + c - '0', c = gc();
  x *= f;
}
template <typename T = int>
inline T read() {
  T res;
  read(res);
  return res;
}
template <typename T, typename... args>
inline void read(T &x, args &...tmp) { read(x), read(tmp...); }
inline void read(char *s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) *s++ = c, c = gc();
}
inline void read(std::string &s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) s += c, c = gc();
}
inline void pc(const char &c) {
  if (pp - outbuf == bufsize) fwrite(outbuf, 1, bufsize, stdout), pp = outbuf;
  *pp++ = c;
}
template <typename T>
inline void print(T x) {
  if (x < 0) x = -x, pc('-');
  static T sta[35];
  T top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) pc(sta[--top] + '0');
}
template <typename T> inline void print(T x, char c) { print(x), pc(c); }
inline void print(char *s) {
  for (; s; ++s) pc(*s);
}
inline void print(const std::string &s) {
  for (const auto &c : s) pc(c);
}
inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
}  // namespace FastIO
using namespace FastIO;
#pragma endregion

using i64 = long long;

constexpr int N = 5050, K = 4, M = 91;
int n, ans;
int cost[N][K], solved[K], canHack[K], score[K], hackCnt[K], partHack[N];
int f[2][M][M][M];
int calcSubScore(int val, int tim) {
  if (!tim) return 0;
  return val * (250 - std::abs(tim)) / 250;
}
int calcPartScore(int u) {
  int res = 0;
  for (int i = 1; i <= 3; i++) res += calcSubScore(score[i], cost[u][i]);
  return res;
}
int dp() {
  std::memset(f, 0, sizeof(f));
  int my = 0;
  for (int i = 1; i <= 3; i++) {
    my += 100 * hackCnt[i] + calcSubScore(score[i], cost[1][i]);
  }
  int cur = 0, lst = 1;
  for (int u = 2; u <= n; u++) {
    if (partHack[u] && calcPartScore(u) > my) {
      cur ^= 1, lst ^= 1;
      for (int i = 0; i <= hackCnt[1]; i++) {
        for (int j = 0; j <= hackCnt[2]; j++) {
          for (int k = 0; k <= hackCnt[3]; k++) {
            f[cur][i][j][k] = f[lst][i][j][k];
          }
        }
      }
      for (int hack1 = 0; hack1 <= 1; hack1++) {
        for (int hack2 = 0; hack2 <= 1; hack2++) {
          for (int hack3 = 0; hack3 <= 1; hack3++) {
            if (hack1 && cost[u][1] >= 0) continue;
            if (hack2 && cost[u][2] >= 0) continue;
            if (hack3 && cost[u][3] >= 0) continue;
            int tmp = calcSubScore(score[1], cost[u][1]) * (!hack1) +
                      calcSubScore(score[2], cost[u][2]) * (!hack2) +
                      calcSubScore(score[3], cost[u][3]) * (!hack3);
            if (tmp > my) continue;
            for (int i = hack1; i <= hackCnt[1]; i++) {
              for (int j = hack2; j <= hackCnt[2]; j++) {
                for (int k = hack3; k <= hackCnt[3]; k++) {
                  f[cur][i][j][k] =
                      std::max(f[cur][i][j][k],
                               f[lst][i - hack1][j - hack2][k - hack3] + 1);
                }
              }
            }
          }
        }
      }
    }
  }
  int res = 1 - f[cur][hackCnt[1]][hackCnt[2]][hackCnt[3]];
  for (int i = 2; i <= n; i++) {
    if (calcPartScore(i) > my) res++;
  }
  return res;
}
void dfs(int u) {
  if (u == 4) {
    ans = std::min(ans, dp());
    return;
  }
  for (int i = 1; i <= 6; i++) {
    int minSolved = (n >> i) + 1;
    if (i == 6) minSolved = 0;
    int maxSolved = n >> (i - 1);
    if (solved[u] >= minSolved && solved[u] - canHack[u] <= maxSolved) {
      score[u] = i * 500;
      hackCnt[u] = std::min(canHack[u], solved[u] - minSolved);
      dfs(u + 1);
    }
  }
}
inline void solve() {
  read(n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 3; j++) {
      read(cost[i][j]);
      solved[j] += !!cost[i][j];
      canHack[j] += cost[i][j] < 0;
      partHack[i] += cost[i][j] < 0;
    }
  }
  if (canHack[1] + canHack[2] + canHack[3] >= 90) {
    print(1, '\n');
    return;
  }
  ans = n;
  dfs(1);
  print(ans, '\n');
}

signed main() {
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  flush();
  return 0;
}