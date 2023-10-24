/**
 * @file    P2292 [HNOI2004] L 语言.cpp
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
constexpr int N = 2e6 + 50, SIG = 26;
struct Acam {
  int tr[N][SIG], nxt[N], end[N], cnt, f[N];
  int convert(char c) { return c - 'a'; }
  int insert(const std::string &s) {
    int p = 0;
    for (auto c : s) {
      int d = convert(c);
      if (!tr[p][d]) tr[p][d] = ++cnt;
      p = tr[p][d];
    }
    end[p]++, f[p] |= 1 << s.length();
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
          f[tr[u][i]] |= f[nxt[tr[u][i]]];
        }
      }
    }
  }
  void calc(const std::string &s) {
    int p = 0, cur = 1, ans = 0;
    for (int i = 0; i < s.length(); i++) {
      p = tr[p][convert(s[i])];
      cur <<= 1;
      if (f[p] & cur) cur |= 1, ans = i + 1;
    }
    std::cout << ans << "\n";
  }
} acam;
}  // namespace ACAM
int n, m;
std::string s;
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> s, ACAM::acam.insert(s);
  ACAM::acam.build();
  for (int i = 1; i <= m; i++) std::cin >> s, ACAM::acam.calc(s);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}