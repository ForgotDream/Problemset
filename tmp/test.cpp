#include <algorithm>
#include <cstdio>
#include <vector>
#define MaxN 200500
using namespace std;
inline int read() {
  int X = 0;
  char ch = 0;
  while (ch < 48 || ch > 57) ch = getchar();
  while (ch >= 48 && ch <= 57) X = X * 10 + (ch ^ 48), ch = getchar();
  return X;
}
struct Node {
  int t[26], f, len;
} a[MaxN << 1];
int tn, las;
char str[MaxN];
void ins(int c) {
  int np = ++tn, p = las;
  las = np;
  a[np].len = a[p].len + 1;
  for (; p && !a[p].t[c]; p = a[p].f) a[p].t[c] = np;
  if (!p)
    a[np].f = 1;
  else {
    int v = a[p].t[c];
    if (a[p].len + 1 == a[v].len)
      a[np].f = v;
    else {
      int nv = ++tn;
      a[nv] = a[v];
      a[nv].len = a[p].len + 1;
      for (; p && a[p].t[c] == v; p = a[p].f) a[p].t[c] = nv;
      a[v].f = a[np].f = nv;
    }
  }
}
int tp[MaxN], dis[MaxN << 1], p[21][MaxN << 2], dfn[MaxN << 1], tim;
bool cmp(int A, int B) { return dfn[A] < dfn[B]; }
vector<int> g[MaxN << 1];
void dfspre(int num) {
  p[0][dfn[num] = ++tim] = num;
  for (int i = 0; i < g[num].size(); i++) {
    dis[g[num][i]] = dis[num] + 1;
    dfspre(g[num][i]);
    p[0][++tim] = num;
  }
}
int lg2[MaxN << 2];
int minp(int u, int v) { return dis[u] < dis[v] ? u : v; }
void InitST() {
  for (int j = 0; (1 << (j + 1)) <= tim; j++)
    for (int i = 1; i + (1 << j) <= tim; i++)
      p[j + 1][i] = minp(p[j][i], p[j][i + (1 << j)]);
  for (int i = 2; i <= tim; i++) lg2[i] = lg2[i / 2] + 1;
}
int lca(int x, int y) {
  x = dfn[x];
  y = dfn[y];
  if (x > y) swap(x, y);
  int j = lg2[y - x + 1];
  return minp(p[j][x], p[j][y - (1 << j) + 1]);
}
int len, q, a1[MaxN], a2[MaxN], in[MaxN << 1], ef, t[MaxN << 1], tot;
inline void add(int pos) {
  if (in[pos] < ef) in[t[++tot] = pos] = ef;
}
int stk[MaxN << 1], top;
long long sum;
int s1[MaxN << 1], s2[MaxN << 1];
void dfs(int num) {
  int sav = s1[num];
  for (int i = 0, v; i < g[num].size(); i++) {
    dfs(v = g[num][i]);
    s1[num] += s1[v];
    s2[num] += s2[v];
  }
  for (int i = 0; i < g[num].size(); i++)
    sum += 1ll * s1[g[num][i]] * (s2[num] - s2[g[num][i]]) * a[num].len;
  sum += 1ll * sav * s2[num] * a[num].len;
}
int main() {
  len = read();
  q = read();
  scanf("%s", str);
  las = tn = 1;
  for (int i = len - 1; i >= 0; i--) ins(str[i] - 'a');
  for (int i = len - 1, p = 1; i >= 0; i--) {
    p = a[p].t[str[i] - 'a'];
    tp[i + 1] = p;
  }
  for (int i = 2; i <= tn; i++) g[a[i].f].push_back(i);
  dfspre(1);
  InitST();
  for (int i = 1; i <= tn; i++) g[i].clear();
  for (int qt = 1, n1, n2; qt <= q; qt++) {
    n1 = read();
    n2 = read();
    ++ef;
    for (int i = 1, sav; i <= n1; i++) {
      add(sav = tp[read()]);
      s1[sav]++;
    }
    for (int i = 1, sav; i <= n2; i++) {
      add(sav = tp[read()]);
      s2[sav]++;
    }
    sort(t + 1, t + tot + 1, cmp);
    int tmp = tot;
    for (int i = 1; i < tmp; i++) add(lca(t[i], t[i + 1]));
    sort(t + 1, t + tot + 1, cmp);
    stk[top = 1] = t[1];
    for (int i = 2; i <= tot; i++) {
      while (lca(stk[top], t[i]) != stk[top]) top--;
      g[stk[top]].push_back(t[i]);
      stk[++top] = t[i];
    }
    sum = 0;
    dfs(t[1]);
    printf("%lld\n", sum);
    for (int i = 1; i <= tot; i++) {
      s1[t[i]] = s2[t[i]] = 0;
      g[t[i]].clear();
    }
    tot = 0;
  }
  return 0;
}
