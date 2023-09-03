/**
 * @file    P3966 [TJOI2013] 单词.cpp
 * @author  ForgotDream
 * @brief   ACAM
 * @date    2023-08-31
 */
#include <cstring>
#include <iostream>
#include <string>
#include <queue>

using i64 = long long;

namespace ACAM {
constexpr int N = 2e6 + 50, SIG = 27;
struct Acam {
  int tr[N][SIG], nxt[N], end[N], deg[N], ans[N], cnt;
  void init() {
    cnt = 0;
    std::memset(tr, 0, sizeof(tr));
    std::memset(nxt, 0, sizeof(nxt));
    std::memset(end, 0, sizeof(end));
  }
  int convert(char c) {
    if (c == ' ') return 26;
    return c - 'a';
  }
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
          nxt[tr[u][i]] = tr[nxt[u]][i];
          deg[tr[nxt[u]][i]]++, q.push(tr[u][i]);
        }
      }
    }
  }
  void topo() {
    std::queue<int> q;
    for (int i = 1; i <= cnt; i++) {
      if (!deg[i]) q.push(i);
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      int v = nxt[u];
      ans[v] += ans[u];
      if (!--deg[v]) q.push(v);
    }
  }
  void query(std::string s) {
    int p = 0;
    for (auto c : s) {
      p = tr[p][convert(c)];
      ans[p]++;
    }
  }
} acam;
}
constexpr int N = 2e6 + 50;
int n, idx[N];
std::string s, t;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> t;
    idx[i] = ACAM::acam.insert(t);
    if (s.empty()) s = t;
    else s = s + " " + t;
  }
  ACAM::acam.build();
  ACAM::acam.query(s);
  ACAM::acam.topo();
  for (int i = 1; i <= n; i++) std::cout << ACAM::acam.ans[idx[i]] << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}