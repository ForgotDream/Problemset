/**
 * @file    CF1202E You Are Given Some Strings....cpp
 * @author  ForgotDream
 * @brief   ACAM
 * @date    2023-08-31
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <queue>
#include <vector>

using i64 = long long;

namespace ACAM {
constexpr int N = 1e6 + 50, SIG = 26;
struct Acam {
  int tr[N][SIG], nxt[N], end[N], cnt;
  int convert(char c) { return c - 'a'; }
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
          nxt[tr[u][i]] = tr[nxt[u]][i], end[tr[u][i]] += end[nxt[tr[u][i]]];
          q.push(tr[u][i]);
        }
      }
    }
  }
  std::vector<int> query(std::string s) {
    int p = 0;
    std::vector<int> res(s.length());
    for (int i = 0; i < s.length(); i++) {
      p = tr[p][convert(s[i])];
      res[i] = end[p];
    }
    return res;
  }
} ac, revac;
}
std::string s, t;
int n;
void solve() {
  std::cin >> s;
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> t;
    ACAM::ac.insert(t);
    std::reverse(t.begin(), t.end());
    ACAM::revac.insert(t);
  }
  ACAM::ac.build();
  ACAM::revac.build();
  auto f = ACAM::ac.query(s);
  std::reverse(s.begin(), s.end());
  auto g = ACAM::revac.query(s);
  std::reverse(g.begin(), g.end());
  i64 ans = 0;
  for (int i = 0; i < s.length() - 1; i++) {
    ans += 1ll * f[i] * g[i + 1];
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}