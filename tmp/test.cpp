#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
#define MAX 200000
inline int read() {
  int x = 0, t = 1;
  char ch = getchar();
  while ((ch < '0' || ch > '9') && ch != '-')
    ch = getchar();
  if (ch == '-')
    t = -1, ch = getchar();
  while (ch <= '9' && ch >= '0')
    x = x * 10 + ch - 48, ch = getchar();
  return x * t;
}
char ss[MAX];
int nd[MAX], n, tot;
int ans[MAX];
int c[MAX];
int dfn[MAX], low[MAX], tim;
int ql[MAX], qr[MAX];
inline int lowbit(int x) { return x & (-x); }
void Modify(int x, int w) {
  while (x <= tim)
    c[x] += w, x += lowbit(x);
}
int getsum(int x) {
  int ret = 0;
  while (x)
    ret += c[x], x -= lowbit(x);
  return ret;
}
struct Node {
  int vis[26];
  int Vis[26];
  int fail, fa;
  int lt;
} t[MAX];
struct Question {
  int x, y, id, ans;
} q[MAX];
bool operator<(Question a, Question b) { return a.y < b.y; }
void GetFail() {
  queue<int> Q;
  for (int i = 0; i < 26; ++i)
    if (t[0].vis[i])
      Q.push(t[0].vis[i]);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int i = 0; i < 26; ++i)
      if (t[u].vis[i])
        t[t[u].vis[i]].fail = t[t[u].fail].vis[i], Q.push(t[u].vis[i]);
      else
        t[u].vis[i] = t[t[u].fail].vis[i];
  }
}
struct Line {
  int v, next;
} e[MAX << 1];
int h[MAX], cnt = 1;
inline void Add(int u, int v) {
  e[cnt] = (Line){v, h[u]};
  h[u] = cnt++;
}
void dfs(int u) {
  dfn[u] = ++tim;
  for (int i = h[u]; i; i = e[i].next)
    dfs(e[i].v);
  low[u] = tim;
}
void DFS(int u) {
  Modify(dfn[u], 1);
  if (t[u].lt)
    for (int i = ql[t[u].lt]; i <= qr[t[u].lt]; ++i)
      q[i].ans = getsum(low[nd[q[i].x]]) - getsum(dfn[nd[q[i].x]] - 1);
  for (int i = 0; i < 26; ++i)
    if (t[u].Vis[i])
      DFS(t[u].Vis[i]);
  Modify(dfn[u], -1);
}
int main() {
  scanf("%s", ss + 1);
  int now = 0;
  for (int i = 1, l = strlen(ss + 1); i <= l; ++i) {
    if (ss[i] >= 'a' && ss[i] <= 'z') {
      if (!t[now].vis[ss[i] - 'a'])
        t[now].vis[ss[i] - 'a'] = ++tot, t[tot].fa = now;
      now = t[now].vis[ss[i] - 'a'];
    }
    if (ss[i] == 'B')
      now = t[now].fa;
    if (ss[i] == 'P') {
      nd[++n] = now;
      t[now].lt = n;
    }
  }
  for (int i = 0; i <= tot; ++i)
    for (int j = 0; j < 26; ++j)
      t[i].Vis[j] = t[i].vis[j];
  int Q = read();
  GetFail();
  for (int i = 1; i <= tot; ++i)
    Add(t[i].fail, i);
  dfs(0);
  for (int i = 1; i <= Q; ++i) {
    q[i].x = read(), q[i].y = read();
    q[i].id = i;
  }
  sort(&q[1], &q[Q + 1]);
  for (int i = 1, pos = 1; i <= Q; i = pos) {
    ql[q[i].y] = i;
    while (q[pos].y == q[i].y)
      pos++;
    qr[q[i].y] = pos - 1;
  }
  DFS(0);
  for (int i = 1; i <= Q; ++i)
    ans[q[i].id] = q[i].ans;
  for (int i = 1; i <= Q; ++i)
    printf("%d\n", ans[i]);
  return 0;
}
