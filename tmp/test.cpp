#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MAX = 233;
const int MAXN = 466;
const int inf = 100000000;
int n, m, s, t;
int b[MAX], p[MAX], ans[MAX], ans2[MAX];
vector<int> a[MAX][MAX];
struct edge {
  int to, cap, rev;
  edge() {}
  edge(int a, int b, int c) { to = a, cap = b, rev = c; }
};
struct Graph {
  vector<edge> e[MAXN];
  queue<int> que;
  int dis[MAXN];
  void addedge(int u, int v, int cap) {
    e[u].push_back(edge(v, cap, e[v].size()));
    e[v].push_back(edge(u, 0, e[u].size() - 1));
  }
  void deledge(int x) { e[x].pop_back(); }
  bool bfs() {
    memset(dis, -1, sizeof dis);
    que.push(s);
    dis[s] = 0;
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (vector<edge>::iterator i = e[u].begin(); i != e[u].end(); i++)
        if (i->cap && dis[i->to] < 0) {
          dis[i->to] = dis[u] + 1;
          que.push(i->to);
        }
    }
    return dis[t] != -1;
  }
  int dfs(int u, int f) {
    if (u == t) return f;
    for (vector<edge>::iterator i = e[u].begin(); i != e[u].end(); i++)
      if (i->cap && dis[i->to] > dis[u]) {
        int d = dfs(i->to, min(f, i->cap));
        if (d) {
          i->cap -= d;
          e[i->to][i->rev].cap += d;
          return d;
        }
      }
    return 0;
  }
  void clear() {
    for (int i = 1; i <= n + m + 2; i++) e[i].clear();
  }
} G[233], tG;
void solveq1() {
  for (int i = 1; i <= m; i++) G[0].addedge(i + n, t, b[i]);
  for (int i = 1; i <= n; i++) {
    G[i] = G[i - 1];
    G[i].addedge(s, i, 1);
    for (int j = 1; j <= m; j++) {
      for (vector<int>::iterator k = a[i][j].begin(); k != a[i][j].end(); k++)
        G[i].addedge(i, *k + n, 1);
      if (G[i].bfs()) {
        G[i].dfs(s, inf);
        ans[i] = j;
        break;
      }
      for (vector<int>::iterator k = a[i][j].begin(); k != a[i][j].end(); k++)
        G[i].deledge(i), G[i].deledge(*k + n);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!ans[i]) ans[i] = m + 1;
    printf("%d ", ans[i]);
  }
  putchar('\n');
}
bool check(int u, int x) {
  tG = G[x - 1];
  tG.addedge(s, u, 1);
  for (int i = 1; i <= p[u]; i++)
    for (vector<int>::iterator j = a[u][i].begin(); j != a[u][i].end(); j++)
      tG.addedge(u, *j + n, 1);
  if (tG.bfs())
    return 1;
  else
    return 0;
}
void solveq2() {
  for (int i = 1; i <= n; i++) {
    if (ans[i] <= p[i]) continue;
    ans2[i] = 1000;
    int l = 1, r = i - 1;
    while (r >= l) {
      int mid = (l + r) >> 1;
      if (check(i, mid))
        ans2[i] = mid, l = mid + 1;
      else
        r = mid - 1;
    }
    if (ans2[i] && ans2[i] != 1000) ans2[i] = i - ans2[i];
  }
  for (int i = 1; i <= n; i++) printf("%d ", ans2[i] == 1000 ? i : ans2[i]);
  putchar('\n');
}
void init() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) a[i][j].clear();
  for (int i = 1; i <= n; i++) ans[i] = ans2[i] = 0;
  G[0].clear();
}
void solve() {
  n = read(), m = read();
  init();
  for (int i = 1; i <= m; i++) b[i] = read();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      int x = read();
      if (x) a[i][x].push_back(j);
    }
  for (int i = 1; i <= n; i++) p[i] = read();
  s = n + m + 1, t = s + 1;
  solveq1();
  solveq2();
}
int main() {
  int T = read(), C = read();
  while (T--) solve();
  return 0;
}
