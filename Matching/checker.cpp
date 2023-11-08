#include <bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define se set<aa>
#define it iterator
#define lb lowber_bound

int n, m, nn, mm, sb;
map<int, int> p;
int a[MAXN], f[MAXN], u[MAXN], tt[MAXN];
int c[MAXN], d[MAXN];
struct aa {
  int l, r, v;
};
set<aa> s[MAXN];
struct op {
  int op, l, r, v;
} opt[MAXN];
int mr[MAXN], srz[MAXN], ak;

bool operator<(aa a, aa b) { return a.r < b.r; }

set<aa> odt;

void fenkuai() {
  sb = sqrt(n);
  for (int i = 1; i <= n + 1; i++) {
    if (i % sb == 1) {
      c[i] = c[i - 1] + 1;
      d[i] = 1;
    } else {
      c[i] = c[i - 1];
      d[i] = d[i - 1] + 1;
    }
  }
  mm = c[n];
}

struct kuai {
  int s[355];

  inline void jia(int x, int y)  // sqrt(n)
  {
    if (srz[x] == 0) return;
    for (int i = srz[x]; i <= mm; i++) s[i] += y;
  }

  inline int sum(int x) {  // O(1)
    return s[x];
  }
} b[355];

inline int read() {
  register int x = 0, ch = getchar();
  while (!isdigit(ch)) ch = getchar();
  while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
  return x;
}

void chonggou(int x) {
  for (int i = 1; i <= c[n]; i++) memset(b[i].s, 0, sizeof(b[i].s));
  memset(srz, 0, sizeof(srz));
  for (int i = x; i <= m && i <= x + sb - 1; i++)
    if (opt[i].op == 2) srz[opt[i].r + 1]++;
  srz[1]++;
  for (int i = 1; i <= n; i++) srz[i] += srz[i - 1];
  srz[n + 1] = 0;
  for (int i = 1; i <= n; i++) b[c[i]].s[srz[f[i]]]++;

  for (int i = 1; i <= mm; i++)
    for (int j = 2; j <= mm; j++) b[i].s[j] += b[i].s[j - 1];
}

void rd() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= m; i++) {
    opt[i].op = read();
    opt[i].l = read();
    opt[i].r = read();

    if (opt[i].op == 1) {
      opt[i].v = read();
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!p.count(a[i])) {
      nn++;
      p[a[i]] = nn;
    }
    s[p[a[i]]].insert((aa){i, i, p[a[i]]});
    odt.insert((aa){i, i, p[a[i]]});
  }
  for (int i = 1; i <= n * 2; i++) {
    s[i].insert((aa){n + 1, n + 1, i});
    s[i].insert((aa){0, 0, i});
  }
  fenkuai();
  for (int i = n; i >= 1; i--) {
    int t = u[p[a[i]]];
    if (t) f[i] = t;
    else f[i] = n + 1;
    u[p[a[i]]] = i;
  }
}

void split(se::it x, int i) {
  int v = x->v, l = x->l, r = x->r;
  if (i < l || i >= r) return;

  s[v].erase((aa){l, r, v});
  s[v].insert((aa){l, i, v});
  s[v].insert((aa){i + 1, r, v});

  odt.erase(x);
  odt.insert((aa){l, i, v});
  odt.insert((aa){i + 1, r, v});
}

aa qls(int v, int x) {
  se::it i = s[v].upper_bound((aa){0, x, 0});
  i--;
  return (*i);
}

inline void qf(int x, int y) {
  if (x == 0) return;
  b[c[x]].jia(f[x], -1);
  f[x] = y;
  b[c[x]].jia(f[x], 1);
}

void dlt(int l, int r, int v) {
  s[v].erase((aa){l, r, v});
  aa ls = qls(v, l);
  aa rs = *s[v].lower_bound((aa){0, r, 0});
  qf(r, r + 1);
  qf(ls.r, rs.l);
}

void jlt(int l, int r, int v) {
  aa ls = qls(v, l);
  aa rs = *s[v].lower_bound((aa){0, r, 0});
  s[v].insert((aa){l, r, v});
  qf(ls.r, l);
  qf(r, rs.l);
}

void assign(int l, int r, int v) {
  se::it x = odt.lower_bound((aa){0, l - 1, 0});
  split(x, l - 1);
  se::it y = odt.lower_bound((aa){0, r, 0});
  split(y, r);

  x = odt.lower_bound((aa){0, l, 0});
  y = odt.lower_bound((aa){0, r + 1, 0});

  for (se::it i = x; i != y;) {
    se::it j = i;
    i++;
    dlt(j->l, j->r, j->v);
    odt.erase(j);
  }

  odt.insert((aa){l, r, v});
  jlt(l, r, v);
}

signed main() {
  rd();
  for (int i = 1; i <= m; i++) {
    if (i % sb == 1) chonggou(i);
    int l = opt[i].l, r = opt[i].r, v = opt[i].v, op = opt[i].op;
    // for (int j = 1; j <= n; j++) std::cout << srz[j] << " \n"[j == n];
    if (op == 1) {
      if (!p.count(v)) {
        nn++;
        p[v] = nn;
      }
      assign(l, r, p[v]);
    } else {
      int ans = r - l + 1;
      if (c[l] != c[r]) {
        int t = srz[r];
        for (int j = c[l] + 1; j <= c[r] - 1; j++) ans -= b[j].sum(t);
        for (int j = l; c[l] == c[j]; j++) ans -= (f[j] <= r);
        for (int j = r; c[r] == c[j]; j--) ans -= (f[j] <= r);
      } else {
        for (int j = l; j <= r; j++) ans -= (f[j] <= r);
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
