/**
 * @file    P4052 [JSOI2007] 文本生成器.cpp
 * @author  ForgotDream
 * @brief   ACAM + DP
 * @date    2023-09-01
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using i64 = long long;

namespace ACAM {
constexpr int N = 1e6 + 50, SIG = 26;
struct Acam {
  int tr[N][SIG], nxt[N], end[N], cnt;
  bool valid[N];
  int convert(char c) { return c - 'A'; }
  int insert(std::string s) {
    int p = 0;
    for (auto c : s) {
      int d = convert(c);
      if (!tr[p][d]) tr[p][d] = ++cnt;
      p = tr[p][d];
    }
    end[p]++, valid[p] = true;
    return p;
  }
  void build() {
    std::queue<int> q;
    for (int i = 0; i < SIG; i++) {
      if (tr[0][i]) q.push(tr[0][i]);
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < SIG; i++) {
        if (!tr[u][i]) {
          tr[u][i] = tr[nxt[u]][i];
        } else {
          nxt[tr[u][i]] = tr[nxt[u]][i], q.push(tr[u][i]);
          valid[tr[u][i]] |= valid[nxt[tr[u][i]]];
        }
      }
    }
  }
} acam;
}  // namespace ACAM
constexpr int mod = 1e4 + 7, N = 105, M = 1e4 + 50;
int n, m;
std::string s;
int f[N][M];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> s;
    ACAM::acam.insert(s);
  }
  ACAM::acam.build();
  f[0][0] = 1;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j <= ACAM::acam.cnt; j++) {
      for (int k = 0; k < ACAM::SIG; k++) {
        if (!ACAM::acam.valid[ACAM::acam.tr[j][k]]) {
          (f[i + 1][ACAM::acam.tr[j][k]] += f[i][j]) %= mod;
        }
      }
    }
  }
  int ans = fastPow(26, m, mod);
  for (int i = 0; i <= ACAM::acam.cnt; i++) (ans -= f[m][i] - mod) %= mod;
  std::cout << (ans + mod) % mod << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}