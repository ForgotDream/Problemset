/**
 * @file    CF163E e-Government.cpp
 * @author  ForgotDream
 * @brief   ACAM + SegTree
 * @date    2023-09-01
 */
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 1e6 + 50;
int n, k;
std::vector<std::string> s;
std::string t;
std::vector<int> adj[M];
namespace ACAM {
constexpr int N = 1e6 + 50, SIG = 26;
struct Acam {
  int tr[N][SIG], nxt[N], end[N], cnt;
  int convert(const char &c) { return c - 'a'; }
  int insert(const std::string &s) {
    int p = 0;
    for (const auto &c : s) {
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
      if (tr[0][i]) q.push(tr[0][i]), adj[1].push_back(tr[0][i] + 1);
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < SIG; i++) {
        if (!tr[u][i]) {
          tr[u][i] = tr[nxt[u]][i];
        } else {
          nxt[tr[u][i]] = tr[nxt[u]][i], q.push(tr[u][i]);
          adj[nxt[tr[u][i]] + 1].push_back(tr[u][i] + 1);
          end[tr[u][i]] += end[nxt[tr[u][i]]];
        }
      }
    }
  }
} acam;
}  // namespace ACAM
namespace HLD {
constexpr int N = 1e6 + 50;
int siz[N], dfn[N], idfn[N], clk;
void dfs(int u, int frm) {
  siz[u] = 1, dfn[u] = ++clk, idfn[clk] = u;
  for (const auto &v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    siz[u] += siz[v];
  }
}
struct BIT {
  int tree[N], n;
  void build() {
    using ACAM::acam;
    n = acam.cnt + 1;
    for (int i = 1; i <= n; i++) {
      add(i, acam.end[idfn[i] - 1] - acam.end[idfn[i - 1] - 1]);
    }
  }
  void add(int u, int val) {
    for (int i = u; i <= n; i += (i & -i)) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= (i & -i)) res += tree[i];
    return res;
  }
} bit;
}
int idx[N];
bool ins[N];
int query(const std::string &s) {
  using ACAM::acam;
  using HLD::bit, HLD::dfn, HLD::siz;
  int p = 0, res = 0;
  for (const auto &c : s) {
    p = acam.tr[p][acam.convert(c)];
    res += bit.query(dfn[p + 1]);
  }
  return res;
}
void solve() {
  std::cin >> n >> k;
  s.resize(k + 1);
  for (int i = 1; i <= k; i++) {
    std::cin >> s[i];
    idx[i] = ACAM::acam.insert(s[i]) + 1;
    ins[i] = true;
  }
  ACAM::acam.build();
  HLD::dfs(1, 0);
  HLD::bit.build();
  for (int i = 1; i <= n; i++) {
    char opt;
    int u;
    std::cin >> opt;
    if (opt == '+') {
      std::cin >> u;
      if (ins[u]) continue;
      ins[u] = true;
      int dfn = HLD::dfn[idx[u]], siz = HLD::siz[idx[u]];
      HLD::bit.add(dfn, 1), HLD::bit.add(dfn + siz, -1);
    } else if (opt == '-') {
      std::cin >> u;
      if (!ins[u]) continue;
      ins[u] = false;
      int dfn = HLD::dfn[idx[u]], siz = HLD::siz[idx[u]];
      HLD::bit.add(dfn, -1), HLD::bit.add(dfn + siz, 1);
    } else {
      std::cin >> t;
      std::cout << query(t) << "\n";
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