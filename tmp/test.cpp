#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define pre(i, a, b) for (int i = a; i >= b; i--)
#define N 2005
#define int long long
using namespace std;
int n, m, k, d[N][N], a[N][N], v[N][N],
    a = 0x7fffffffffffffffLL,
    op[2] = {0x3f3f3f3f3f3f3f3fLL, 0x3f3f3f3f3f3f3f3fLL};
typedef pair<int, int> Pr;
queue<Pr> q;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
void bfs(int x, int y, int c) {
  while (!q.empty()) q.pop();
  memset(d, 0x3f, sizeof(d));
  memset(v, 0, sizeof(v));
  v[x][y] = 1;
  d[x][y] = 0;
  q.push(make_pair(x, y));
  while (!q.empty()) {
    Pr cur = q.front();
    q.pop();
    int x = cur.first, y = cur.second;
    if (a[x][y]) op[c] = min(op[c], d[x][y] * k + a[x][y]);
    rep(i, 0, 3) {
      int xx = x + dx[i], yy = y + dy[i];
      if (!v[xx][yy] && xx >= 1 && yy >= 1 && xx <= n && yy <= m &&
          ~a[xx][yy]) {
        d[xx][yy] = d[x][y] + 1;
        v[xx][yy] = 1;
        q.push(make_pair(xx, yy));
      }
    }
  }
}
signed main() {
  scanf("%lld%lld%lld", &n, &m, &k);
  rep(i, 1, n) rep(j, 1, m) scanf("%lld", &a[i][j]);
  bfs(1, 1, 0);
  bfs(n, m, 1);
  if (v[1][1]) a = min(a, d[1][1] * k);
  a = min(a, op[0] + op[1]);
  if (a >= 0x3f3f3f3f3f3f3f3fLL) {
    puts("-1");
    return 0;
  }
  printf("%lld\n", min(a, op[0] + op[1]));
  return 0;
}