/**
 * @file    P3041 [USACO12JAN] Video Game G.cpp
 * @author  ForgotDream
 * @brief   ACAM
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
constexpr int N = 1050, SIG = 26;
struct Acam {
  int tr[N][SIG], nxt[N], end[N], cnt;
  int convert(char c) { return c - 'A'; }
  int insert(std::string s) {
    int p = 0;
    for (auto c : s) {
      int d = convert(c);
      if (!tr[p][d]) tr[p][d] = ++cnt;
      p = tr[p][d];
    }
    end[p]++;
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
          end[tr[u][i]] += end[nxt[tr[u][i]]];
        }
      }
    }
  }
  int f[1050][N];
  int calc(int n) {
    std::memset(f, -0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= cnt; j++) {
        for (int k = 0; k < SIG; k++) {
          f[i + 1][tr[j][k]] =
              std::max(f[i + 1][tr[j][k]], f[i][j] + end[tr[j][k]]);
        }
      }
    }
    int max = 0;
    for (int i = 0; i <= cnt; i++) max = std::max(max, f[n][i]);
    return max;
  }
} acam;
}  // namespace ACAM
int n, k;
std::string s;
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> s, ACAM::acam.insert(s);
  ACAM::acam.build();
  std::cout << ACAM::acam.calc(k) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}