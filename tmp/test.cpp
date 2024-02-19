#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
const int inf = 0x3f3f3f3f;
struct Node {
  int Min, Max;
  long long sum1, sum2;
} tr[maxn * 40];
struct Segment_Tree {
  int son[maxn * 40][2], tot;
  Node merge(const Node &a, const Node &b) {
    Node c;
    c.Min = min(a.Min, b.Min);
    c.Max = max(a.Max, b.Max);
    c.sum1 = a.sum1 + b.sum1 + b.Min * 1LL * (b.Min - a.Max);
    c.sum2 = a.sum2 + b.sum2 + b.Min - a.Max;
    return c;
  }
  int Find_Max(int l, int r, int rt, int L, int R) {
    if (!rt) return 0;
    if (L <= l && r <= R) return tr[rt].Max;
    int mid = l + r >> 1, ans = 0;
    if (L <= mid) ans = Find_Max(l, mid, son[rt][0], L, R);
    if (R > mid) ans = max(ans, Find_Max(mid + 1, r, son[rt][1], L, R));
    return ans;
  }
  int Find_Min(int l, int r, int rt, int L, int R) {
    if (!rt) return inf;
    if (L <= l && r <= R) return tr[rt].Min;
    int mid = l + r >> 1, ans = inf;
    if (L <= mid) ans = Find_Min(l, mid, son[rt][0], L, R);
    if (R > mid) ans = min(ans, Find_Min(mid + 1, r, son[rt][1], L, R));
    return ans;
  }
  Node tmp;
  void Query(int l, int r, int rt, int L, int R) {
    if (!rt) return;
    if (L <= l && r <= R) {
      if (tmp.Min == 0)
        tmp = tr[rt];
      else
        tmp = merge(tmp, tr[rt]);
      return;
    }
    int mid = l + r >> 1;
    if (L <= mid) Query(l, mid, son[rt][0], L, R);
    if (R > mid) Query(mid + 1, r, son[rt][1], L, R);
  }
  void update(int l, int r, int &rt, int p) {
    if (!rt) rt = ++tot;
    if (l == r) {
      tr[rt].Min = tr[rt].Max = p;
      tr[rt].sum1 = tr[rt].sum2 = 0;
      return;
    }
    int mid = l + r >> 1;
    if (p <= mid)
      update(l, mid, son[rt][0], p);
    else
      update(mid + 1, r, son[rt][1], p);
    if (son[rt][0] && son[rt][1])
      tr[rt] = merge(tr[son[rt][0]], tr[son[rt][1]]);
    else if (son[rt][0])
      tr[rt] = tr[son[rt][0]];
    else
      tr[rt] = tr[son[rt][1]];
  }
  int Merge(int x, int y) {
    if (!x || !y) return x + y;
    int rt = ++tot;
    son[rt][0] = Merge(son[x][0], son[y][0]);
    son[rt][1] = Merge(son[x][1], son[y][1]);
    if (son[rt][0] && son[rt][1])
      tr[rt] = merge(tr[son[rt][0]], tr[son[rt][1]]);
    else if (son[rt][0])
      tr[rt] = tr[son[rt][0]];
    else
      tr[rt] = tr[son[rt][1]];
    return rt;
  }
} T;
int root[maxn], cnt = 0, lst;
int son[maxn][10], fa[maxn];
int len[maxn], pos[maxn], up[maxn][19], dep[maxn];
void Add(int c, int id) {
  int cur = ++cnt, p = lst;
  lst = pos[id] = cur, len[cur] = len[p] + 1;
  while (p && !son[p][c]) son[p][c] = cur, p = fa[p];
  if (!p)
    fa[cur] = 1;
  else {
    int q = son[p][c];
    if (len[p] + 1 == len[q])
      fa[cur] = q;
    else {
      int nq = ++cnt;
      len[nq] = len[p] + 1;
      memcpy(son[nq], son[q], sizeof(son[q]));
      fa[nq] = fa[q], fa[q] = fa[cur] = nq;
      while (p && son[p][c] == q) son[p][c] = nq, p = fa[p];
    }
  }
}
int n;
int head[maxn], ecnt = 0;
struct edge {
  int v, nxt;
} e[maxn << 1];
void add(int u, int v) { e[++ecnt] = (edge){v, head[u]}, head[u] = ecnt; }
void dfs(int u) {
  up[u][0] = fa[u];
  for (int i = 1; i <= 18; i++) up[u][i] = up[up[u][i - 1]][i - 1];
  for (int i = head[u]; ~i; i = e[i].nxt) {
    int v = e[i].v;
    dep[v] = dep[u] + 1;
    dfs(v);
    if (u != 1) root[u] = T.Merge(root[u], root[v]);
  }
}
void build() {
  memset(head, -1, sizeof(head)), ecnt = 0;
  for (int i = 1; i <= cnt; i++)
    if (fa[i]) add(fa[i], i);
  for (int i = 1; i <= n; i++) T.update(1, n, root[pos[i]], i);
  dfs(1);
}
long long C(int len) {
  if (len < 2) return 0;
  return len * 1LL * (len - 1) / 2;
}
long long query(int l, int r) {
  int Len = r - l + 1, u = pos[r];
  for (int i = 18; i >= 0; i--)
    if (len[up[u][i]] >= Len) u = up[u][i];
  int L = tr[root[u]].Min, R = tr[root[u]].Max;
  // std::cerr << u << " " << L << " " << R << "\n";
  if (L < R - Len * 2 + 1 &&
      T.Find_Max(1, n, root[u], L, R - Len) - Len + 1 > L)
    return C(n - 1);
  if (R - Len + 1 <= L) {
    Node now = tr[root[u]];
    int lm = R - Len + 1;
    long long ans =
        now.sum1 - now.sum2 * lm + C(L - lm) + (L - lm) * 1LL * (n - Len);
    return C(n - 1) - ans;
  } else {
    T.tmp = (Node){0, 0, 0, 0};
    int lm = R - Len + 1, poslm = T.Find_Max(1, n, root[u], 1, lm);
    T.Query(1, n, root[u], poslm, L + Len - 1);
    Node now = T.tmp;
    int p1 = T.Find_Max(1, n, root[u], 1, L + Len - 1);
    int p2 = T.Find_Min(1, n, root[u], L + Len, n);
    long long ans = now.sum1 - now.sum2 * lm +
                    (p2 > lm ? (L - (p1 - Len + 1)) * 1LL * (p2 - lm) : 0);
    return C(n - 1) - ans;
  }
}
char s[maxn];
int q;
int main() {
  scanf("%d%d", &n, &q);
  scanf("%s", s + 1);
  cnt = lst = 1;
  for (int i = 1; i <= n; i++) Add(s[i] - '0', i);
  build();
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%lld\n", query(l, r));
  }
}
