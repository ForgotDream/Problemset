#include <bits/stdc++.h>
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
typedef pair<i64, i64> pii;
const int N = 1000, Inf = 0x3f3f3f3f, M = 2 * 1e6 + 50;
int n, m, head[N], edge_sum = 1, a[N];
struct edge {
  int nst, to, op;
} e[N << 1];
int w[M], from[M];
i64 bfs(int si) {
  vector<int> dis(n + 1, Inf);
  dis[si] = a[si];
  vector<bool> vis(n + 1, false);
  vis[si] = true;
  queue<int> q;
  q.push(si);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = false;
    for (int i = head[u]; i; i = e[i].nst) {
      int v = e[i].to;
      if (e[i].op == -1) continue;
      if (dis[u] == Inf) continue;
      if (e[i].op == 0 && dis[v] > dis[u] + 1) {
        dis[v] = dis[u] + 1;
        if (!vis[v]) {
          q.push(v);
          vis[v] = true;
        }
      }
      if (e[i].op == 1 && dis[v] > from[dis[u]]) {
        dis[v] = from[dis[u]];
        if (!vis[v]) {
          q.push(v);
          vis[v] = true;
        }
      }
    }
  }
  i64 sum = 0;
  for (int i = 1; i <= n; i++) {
    if (dis[i] == Inf) return 0;
    sum += dis[i];
  }
  return sum;
}
i64 calc() {
  i64 S = 0;
  for (int i = 1; i <= n; i++) {
    S += bfs(i);
  }
  return S;
}
void _init() {
  for (int i = 1; i <= 1e6; i++) {
    w[i] = i - (i / 20 + (i % 20 > 0));
    if (from[w[i]] == 0) from[w[i]] = i;
  }
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  _init();
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1, u, v, op; i <= m; i++) {
    cin >> u >> v >> op;
    e[++edge_sum] = {head[u], v, op};
    head[u] = edge_sum;
    e[++edge_sum] = {head[v], u, op};
    head[v] = edge_sum;
  }
  cout << calc() << " ";
  i64 maxn = 0;
  for (int i = 2; i <= edge_sum; i += 2) {
    int mark = e[i].op;
    e[i].op = e[i ^ 1].op = -1;
    maxn = max(maxn, calc());
    e[i].op = e[i ^ 1].op = mark;
  }
  cout << maxn << endl;
  return 0;
}
