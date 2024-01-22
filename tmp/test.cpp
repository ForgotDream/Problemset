#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;
typedef long long ll;
template <class T>
void read(T &x) {
  char c;
  bool op = 0;
  while (c = getchar(), c < '0' || c > '9')
    if (c == '-') op = 1;
  x = c - '0';
  while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + c - '0';
  if (op) x = -x;
}
template <class T>
void write(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x >= 10) write(x / 10);
  putchar('0' + x % 10);
}

const int INF = 0x3f3f3f3f;
int n, m, K, root, f[101][1111], a[101], ans[11][11];
bool inq[101];
typedef pair<int, int> par;
typedef pair<par, int> rec;
#define fi first
#define se second
#define mp make_pair
#define num(u) (u.fi * m + u.se)
rec pre[101][1111];
const int dx[] = {0, 0, -1, 1};
const int dy[] = {1, -1, 0, 0};
queue<par> que;

bool legal(par u) { return u.fi >= 0 && u.se >= 0 && u.fi < n && u.se < m; }
void spfa(int now) {
  while (!que.empty()) {
    par u = que.front();
    que.pop();
    inq[num(u)] = 0;
    for (int d = 0; d < 4; d++) {
      par v = mp(u.fi + dx[d], u.se + dy[d]);
      int nu = num(u), nv = num(v);
      if (legal(v) && f[nv][now] > f[nu][now] + a[nv]) {
        f[nv][now] = f[nu][now] + a[nv];
        if (!inq[nv]) inq[nv] = 1, que.push(v);
        pre[nv][now] = mp(u, now);
      }
    }
  }
}
void dfs(par u, int now) {
  if (!pre[num(u)][now].se) return;
  ans[u.fi][u.se] = 1;
  int nu = num(u);
  if (pre[nu][now].fi == u) dfs(u, now ^ pre[nu][now].se);
  dfs(pre[nu][now].fi, pre[nu][now].se);
}

int main() {
  read(n), read(m);
  memset(f, 0x3f, sizeof(f));
  for (int i = 0, tot = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      read(a[tot]);
      if (!a[tot]) f[tot][1 << (K++)] = 0, root = tot;
      tot++;
    }
  for (int now = 1; now < (1 << K); now++) {
    for (int i = 0; i < n * m; i++) {
      for (int s = now & (now - 1); s; s = now & (s - 1))
        if (f[i][now] > f[i][s] + f[i][now ^ s] - a[i]) {
          f[i][now] = f[i][s] + f[i][now ^ s] - a[i];
          pre[i][now] = mp(mp(i / m, i % m), s);
        }
      if (f[i][now] < INF) que.push(mp(i / m, i % m)), inq[i] = 1;
    }
    spfa(now);
  }
  write(f[root][(1 << K) - 1]), enter;
  dfs(mp(root / m, root % m), (1 << K) - 1);
  for (int i = 0, tot = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      if (!a[tot++])
        putchar('x');
      else
        putchar(ans[i][j] ? 'o' : '_');
    enter;
  }

  return 0;
}
