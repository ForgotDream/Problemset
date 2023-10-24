/**
 * @file    CF1437G Death DBMS.cpp
 * @author  ForgotDream
 * @brief   ACAM
 * @date    2023-09-01
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, m, idx[N], val[N];
std::multiset<int> se[N];
std::string s;
namespace ACAM {
constexpr int N = 3e5 + 50, SIG = 26;
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
    end[p]++, se[p].insert(0);
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
        }
      }
    }
  }
  std::stack<int> st;
  bool ins[N];
  int query(std::string s) {
    int p = 0, res = -1;
    for (auto c : s) {
      p = tr[p][convert(c)];
      for (int j = p; j && !ins[j]; j = nxt[j]) {
        if (!se[j].empty()) res = std::max(*se[j].rbegin(), res);
        st.push(j), ins[j] = true;
      }
    }
    while (!st.empty()) ins[st.top()] = false, st.pop();
    return res;
  }
} acam;
}
void solve() {
  using ACAM::acam;
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> s;
    idx[i] = acam.insert(s);
  }
  acam.build();
  for (int i = 1; i <= m; i++) {
    int opt, u, v;
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> u >> v;
      se[idx[u]].erase(se[idx[u]].find(val[u]));
      val[u] = v;
      se[idx[u]].insert(val[u]);
    } else {
      std::cin >> s;
      std::cout << acam.query(s) << "\n";
    }
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}