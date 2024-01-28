#include <cstdio>
#include <iostream>
#define N 100010
#define kar k[i].ar
#define trar tr[i].ar
#define min(a, b) (a < b ? a : b)
using namespace std;
int a, b, t, n, m, f[N], ans, trl;
struct node {
  int next, ar, flow;
} k[N * 20], tr[N * 20];
int trf[N], ss;
int first[N], dis[N], len;
int x[N], y[N], v[N], e[N];
int t1[N], t2[N], tl1, tl2;
void add(int a, int b, int t) {
  len++;
  k[len].ar = b;
  k[len].next = first[a];
  first[a] = len;
  k[len].flow = t;
}
void adtr(int a, int b, int t) {
  trl++;
  tr[trl].ar = b;
  tr[trl].next = trf[a];
  trf[a] = trl;
  tr[trl].flow = t;
}
int head, tail, d[N];
bool bfs() {
  head = 0, tail = 1;
  d[0] = a;
  for (int i = 0; i <= n; i++) dis[i] = 0;
  dis[a] = 1;
  while (head < tail) {
    t = d[head];
    head++;
    for (int i = first[t]; i; i = k[i].next) {
      if (dis[kar] == 0 && k[i].flow > 0) {
        dis[kar] = dis[t] + 1;
        if (kar == b) return true;
        d[tail] = kar;
        tail++;
      }
    }
  }
  return false;
}
int dfs(int xx, int flow) {
  if (xx == b) return flow;
  if (flow == 0) return 0;
  if (dis[xx] >= dis[b]) return 0;
  int h, s = 0;
  for (int i = first[xx]; i > 1; i = k[i].next) {
    if (flow == 0) {
      dis[xx] = 0;
      break;
    }
    if (dis[kar] == dis[xx] + 1 && k[i].flow > 0) {
      h = dfs(kar, min(flow, k[i].flow));
      s += h;
      flow -= h;
      k[i].flow -= h;
      k[i ^ 1].flow += h;
      if (h == 0) dis[kar] = 0;
    }
  }
  return s;
}
void dinic() {
  for (int i = 0; i <= n; i++) {
    dis[i] = 0;
    first[i] = 0;
  }
  len = 1, ans = 0;
  for (int i = 1; i <= m; i++)
    add(x[i], y[i], f[i]), add(y[i], x[i], f[i]);
  while (bfs()) ans += dfs(a, 0x7ffffff);
}
void build(int l, int r) {
  if (l >= r) return;
  a = v[l];
  b = v[l + 1];
  dinic();
  adtr(a, b, ans);
  adtr(b, a, ans);
  int tl1 = 0, tl2 = 0;
  for (int i = l; i <= r; i++) {
    if (dis[v[i]])
      tl1++, t1[tl1] = v[i];
    else
      tl2++, t2[tl2] = v[i];
  }
  std::cerr << a << " " << b << " " << ans << "\n";
  for (int i = 1; i <= tl1; i++) v[i + l - 1] = t1[i];
  for (int i = 1; i <= tl2; i++) v[l + tl1 + i - 1] = t2[i];
  build(l, tl1 + l - 1);
  build(l + tl1, r);
}
int findans() {
  head = 0, tail = 1;
  d[head] = a;
  for (int i = 0; i <= n; i++) dis[i] = 0;
  dis[a] = 0x7ffffff;
  while (head < tail) {
    t = d[head];
    head++;
    for (int i = trf[t]; i; i = tr[i].next) {
      if (dis[trar] == 0) {
        dis[trar] = min(dis[t], tr[i].flow + 1);
        if (trar == b) return dis[b] - 1;
        d[tail] = trar;
        tail++;
      }
    }
  }
  return dis[b] - 1;
}
int main() {
  int T;
  len = 1;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &a, &b, &t);
    x[i] = a, y[i] = b, f[i] = t;
  }
  for (int i = 0; i <= n; i++) v[i] = i;
  build(0, n);
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &a, &b);
    printf("%d\n", findans());
  }
  return 0;
}
