#include <bits/stdc++.h>
using namespace std;
typedef long double lf;
const int N = 5e5 + 5;
int n, a[N], fa[N];
lf p[N], g[N], ans, k[N], b[N];
vector<int> e[N];
void dfs1(int x) {
  g[x] = p[x];
  for (auto v : e[x]) dfs1(v), g[x] *= 1.0 - g[v];
}
void dfs2(int x) {
  if (k[x] + b[x] > 0) ans += g[x] * (k[x] + b[x]);
  lf W = p[x];
  for (auto v : e[x]) W *= 1.0 - g[v];
  for (auto v : e[x]) {
    lf o = W / (1.0 - g[v]);
    k[v] = -k[x] * o - o * a[x];
    b[v] = k[x] * o + b[x] + o * a[x];
    dfs2(v);
  }
}
int main() {
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 2; i <= n; ++i) {
    scanf("%d", &fa[i]);
    e[fa[i]].push_back(i);
  }
  for (int i = 1; i <= n; ++i) scanf("%Lf", &p[i]);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  dfs1(1);
  dfs2(1);
  printf("%Lf\n", ans);
  return 0;
}
