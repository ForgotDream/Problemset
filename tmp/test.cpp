#include <algorithm>
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int rd() {
  int x = 0, f = 1, c = getchar();
  while (((c - '0') | ('9' - c)) < 0) f = c != '-', c = getchar();
  while (((c - '0') | ('9' - c)) > 0) x = x * 10 + c - '0', c = getchar();
  return f ? x : -x;
}

const int N = 1e6;
const int SIGMA = 2;

int n, m;

struct node {
  int ch[SIGMA], lnk;
  int len;
} t[2 * N + 5];
int alct = 1;
int ins(int p, int c) {
  if (t[p].ch[c]) {
    int q = t[p].ch[c];
    if (t[p].len + 1 != t[q].len) {
      int v = ++alct;
      t[v] = t[q], t[v].len = t[p].len + 1;
      t[q].lnk = v;
      for (; p && t[p].ch[c] == q; p = t[p].lnk) t[p].ch[c] = v;
      return v;
    } else
      return q;
  }
  int u = ++alct;
  t[u].len = t[p].len + 1;
  for (; p && !t[p].ch[c]; p = t[p].lnk) t[p].ch[c] = u;
  if (p) {
    int q = t[p].ch[c];
    if (t[p].len + 1 != t[q].len) {
      int v = ++alct;
      t[v] = t[q], t[v].len = t[p].len + 1;
      t[q].lnk = t[u].lnk = v;
      for (; p && t[p].ch[c] == q; p = t[p].lnk) t[p].ch[c] = v;
    } else
      t[u].lnk = q;
  } else
    t[u].lnk = 1;
  return u;
}

int L[N + 5], f[N + 5];
bool check(int x, int len) {
  static int q[N + 5];
  int hd = 1, tl = 0;
  q[++tl] = 0;
  for (int i = 0; i < x; i++) f[i] = 0;
  for (int i = x; i <= len; i++) {
    f[i] = f[i - 1];
    while (hd <= tl && f[q[tl]] - q[tl] <= f[i - x] - (i - x)) tl--;
    q[++tl] = i - x;
    while (hd <= tl && q[hd] < i - L[i]) hd++;
    if (hd <= tl) f[i] = std::max(f[i], f[q[hd]] + i - q[hd]);
  }
  return 9 * len <= 10 * f[len];
}

void solve(char *s, int len) {
  int p = 1;
  for (int i = 0, mxl = 0; i < len; i++) {
    while (p != 1 && !t[p].ch[s[i] - '0']) p = t[p].lnk, mxl = t[p].len;
    if (t[p].ch[s[i] - '0'])
      p = t[p].ch[s[i] - '0'], mxl = std::min(mxl + 1, t[p].len);
    L[i + 1] = mxl;
  }
  int l = 1, r = len, ans;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid, len))
      l = mid + 1, ans = mid;
    else
      r = mid - 1;
  }
  printf("%d\n", ans);
}

char buf[N + 5];
int main() {
  n = rd(), m = rd();
  for (int i = 1; i <= m; i++) {
    scanf("%s", buf);
    int len = strlen(buf);
    int lst = 1;
    for (int i = 0; i < len; i++) {
      lst = ins(lst, buf[i] - '0');
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf("%s", buf), solve(buf, strlen(buf));
  }
  return 0;
}
