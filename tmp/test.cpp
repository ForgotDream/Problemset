#include <cstdio>
#include <vector>
using namespace std;
const int M = 2000005;
const int MOD = 1e9 + 7;
int read() {
  int x = 0, f = 1;
  char c;
  while ((c = getchar()) < '0' || c > '9') {
    if (c == '-') f = -1;
  }
  while (c >= '0' && c <= '9') {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x * f;
}
int n, m, k, a[M], b[M], c[M], l[M], nx[M], fa[M];
vector<int> g[M];
int find(int x) {
  if (x != fa[x]) fa[x] = find(fa[x]);
  return fa[x];
}
int qkpow(int a, int b) {
  int r = 1;
  while (b > 0) {
    if (b & 1) r = 1ll * r * a % MOD;
    a = 1ll * a * a % MOD;
    b >>= 1;
  }
  return r;
}
int dfs(int u) {
  for (int v : g[u]) {
    if (~c[v]) {
      if (c[v] == c[u]) return 0;
      continue;
    }
    c[v] = c[u] ^ 1;
    if (!dfs(v)) return 0;
  }
  return 1;
}
signed main() {
  n = read();
  for (int i = 1; i <= n; i++) b[read()] = b[read()] = i, c[i] = -1;
  for (int i = 1; i <= 2 * n; i++) fa[i] = nx[i] = i;
  for (int i = 1; i <= 2 * n; i++) {
    int u = b[i];
    if (!l[u]) {
      a[++m] = u, l[u] = m;
      continue;
    }
    for (int j = fa[l[u]] = find(l[u] + 1); j <= m;) {
      g[a[j]].push_back(u);
      g[u].push_back(a[j]);
      int t = find(nx[j] + 1);
      nx[j] = m;
      j = t;
    }
  }
  for (int i = 1; i <= n; i++)
    if (c[i] == -1 && (k++, c[i] = 0, !dfs(i))) {
      puts("0");
      return 0;
    }
  printf("%d\n", qkpow(2, k));
}
