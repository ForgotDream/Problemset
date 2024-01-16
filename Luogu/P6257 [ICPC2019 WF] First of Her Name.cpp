/*
 * @file    P6257 [ICPC2019 WF] First of Her Name.cpp
 * @author  ForgotDream
 * @brief   ACAM
 * @date    2024-01-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 50;

int n, k;

struct ACAM {
  int ch[N][26], nxt[N], cnt;
  int insert(std::string_view s) {
    int p = 0;
    for (auto c : s) {
      int d = c - 'A';
      if (!ch[p][d]) ch[p][d] = ++cnt;
      p = ch[p][d];
    }
    return p;
  }
  void build() {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) if (ch[0][i]) q.push(ch[0][i]);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < 26; i++) {
        int &v = ch[u][i];
        if (!v) v = ch[nxt[u]][i];
        else nxt[v] = ch[nxt[u]][i], q.push(v);
      }
    }
  }
} ac;

int pos[N], ch[N][26];
i64 ans[N];

std::vector<int> adj[N];

void dfs(int u, int p) {
  ans[p]++;
  for (int i = 0; i < 26; i++) {
    if (!ch[u][i]) continue;
    dfs(ch[u][i], ac.ch[p][i]);
  }
}

void traverse(int u) {
  for (auto v : adj[u]) traverse(v), ans[u] += ans[v];
}

void solve() {
  std::cin >> n >> k;
  for (int i = 1, f; i <= n; i++) {
    char c;
    std::cin >> c >> f, ch[f][c - 'A'] = i;
  }

  for (int i = 1; i <= k; i++) {
    std::string t;
    std::cin >> t, std::reverse(t.begin(), t.end());
    pos[i] = ac.insert(t);
  }
  ac.build();
  for (int i = 1; i <= ac.cnt; i++) adj[ac.nxt[i]].push_back(i);

  dfs(0, 0), traverse(0);
  for (int i = 1; i <= k; i++) std::cout << ans[pos[i]] << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
