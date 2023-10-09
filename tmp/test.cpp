#include <cstdio>
typedef long long ll;
int a[100005], st[100005], g[100005][25], f[100005][25];
inline int read() {
  register int x = 0, f = 1;
  register char s = getchar();
  while (s > '9' || s < '0') {
    if (s == '-') f = -1;
    s = getchar();
  }
  while (s >= '0' && s <= '9') {
    x = x * 10 + s - '0';
    s = getchar();
  }
  return x * f;
}
inline void swap(int &x, int &y) {
  int tmp = x;
  x = y;
  y = tmp;
}
inline int min(const int &x, const int &y) { return x < y ? x : y; }
inline int max(const int &x, const int &y) { return x > y ? x : y; }
int main() {
  int n = read(), m = read(), Q = read(), top = 0;
  for (register int i = 1; i <= n; ++i) a[i] = read();
  top = 0;
  st[++top] = 1;
  for (register int i = 1; i <= n; ++i) {
    while (top && a[st[top]] < a[i]) --top;
    f[i][0] = st[top];
    st[++top] = i;
  }
  top = 0;
  st[++top] = n;
  for (register int i = n; i >= 1; --i) {
    while (top && a[st[top]] < a[i]) --top;
    g[i][0] = st[top];
    st[++top] = i;
  }
  for (register int j = 1; j <= 20; ++j) {
    for (register int i = 1; i <= n; ++i) {
      f[i][j] = min(f[f[i][j - 1]][j - 1], f[g[i][j - 1]][j - 1]);
      g[i][j] = max(g[g[i][j - 1]][j - 1], g[f[i][j - 1]][j - 1]);
    }
  }
  for (register int i = 1; i <= Q; ++i) {
    int x = read(), y = read(), l, r;
    ll ans = 0;
    if (x > y) swap(x, y);
    l = r = x;
    for (register int j = 20; j >= 0; --j) {
      int nxtL = min(f[l][j], f[r][j]), nxtR = max(g[l][j], g[r][j]);
      if (nxtR < y) {
        l = nxtL, r = nxtR;
        ans += (1 << j);
      }
    }
    x = r;
    l = r = y;
    for (register int j = 20; j >= 0; --j) {
      int nxtL = min(f[l][j], f[r][j]), nxtR = max(g[l][j], g[r][j]);
      if (nxtL > x) {
        l = nxtL, r = nxtR;
        ans += (1 << j);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
